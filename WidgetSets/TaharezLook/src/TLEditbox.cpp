/************************************************************************
	filename: 	TLEditbox.cpp
	created:	29/5/2004
	author:		Paul D Turner
	
	purpose:	Implementation of Taharez Look Editbox widget
*************************************************************************/
/*************************************************************************
    Crazy Eddie's GUI System (http://crayzedsgui.sourceforge.net)
    Copyright (C)2004 Paul D Turner (crayzed@users.sourceforge.net)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************/
#include "TLEditbox.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIFont.h"

// Start of CEGUI namespace section
namespace CEGUI
{
/*************************************************************************
	Constants
*************************************************************************/
// image name constants
const utf8	TLEditbox::ImagesetName[]				= "TaharezImagery";
const utf8	TLEditbox::ContainerLeftImageName[]		= "EditBoxLeft";
const utf8	TLEditbox::ContainerMiddleImageName[]	= "EditBoxMiddle";
const utf8	TLEditbox::ContainerRightImageName[]	= "EditBoxRight";
const utf8	TLEditbox::CaratImageName[]				= "EditBoxCarat";
const utf8	TLEditbox::SelectionBrushImageName[]	= "TextSelectionBrush";
const utf8	TLEditbox::MouseCursorImageName[]		= "MouseTextBar";

// layout values
const float	TLEditbox::TextPaddingRatio		= 0.5f;

// implementation constantss
const uint	TLEditbox::SelectionLayer	= 1;
const uint	TLEditbox::TextLayer		= 2;
const uint	TLEditbox::CaratLayer		= 3;


/*************************************************************************
	Constructor for Taharez edit box widgets	
*************************************************************************/
TLEditbox::TLEditbox(const String& type, const String& name) :
	Editbox(type, name),
	d_lastTextOffset(0)
{
	Imageset* iset = ImagesetManager::getSingleton().getImageset(ImagesetName);
	
	// cache images to be used
	d_left		= &iset->getImage(ContainerLeftImageName);
	d_middle	= &iset->getImage(ContainerMiddleImageName);
	d_right		= &iset->getImage(ContainerRightImageName);
	d_carat		= &iset->getImage(CaratImageName);
	d_selection	= &iset->getImage(SelectionBrushImageName);

	setMouseCursor(&iset->getImage(MouseCursorImageName));
}


/*************************************************************************
	Destructor for Taharez edit box widgets	
*************************************************************************/
TLEditbox::~TLEditbox(void)
{
}


/*************************************************************************
	Return the text code point index that is rendered closest to screen
	position 'pt'.	
*************************************************************************/
ulong TLEditbox::getTextIndexFromPosition(const Point& pt) const
{
	//
	// calculate final window position to be checked
	//
	float wndx = screenToWindowX(pt.d_x);

	if (getMetricsMode() == Relative)
	{
		wndx = relativeToAbsoluteX(wndx);
	}

	wndx -= d_lastTextOffset;

	//
	// Return the proper index
	//
	if (isTextMasked())
	{
		return getFont()->getCharAtPixel(String(d_text.length(), getMaskCodePoint()), 0, wndx);
	}
	else
	{
		return getFont()->getCharAtPixel(d_text, 0, wndx);
	}
	
}


/*************************************************************************
	return text padding value to use in pixels	
*************************************************************************/
float TLEditbox::getTextPaddingPixels(void) const
{
	return d_left->getWidth() * TextPaddingRatio;
}


/*************************************************************************
	Perform the actual rendering for this Window.
*************************************************************************/
void TLEditbox::drawSelf(float z)
{
	Rect clipper(getPixelRect());

	// do nothing if the widget is totally clipped.
	if (clipper.getWidth() == 0)
	{
		return;
	}

	const Font* fnt = getFont();
	Renderer*	renderer = System::getSingleton().getRenderer();

	// get the destination screen rect for this window
	Rect absrect(getUnclippedPixelRect());

	// calculate colours to use.
	colour alpha_comp = ((colour)(getEffectiveAlpha() * 255.0f) << 24);
	colour colval = alpha_comp | 0xFFFFFF;
	ColourRect colours(colval, colval, colval, colval);

	bool hasFocus = hasInputFocus();

	//
	// render container
	//
	// calculate widths for container segments
	float leftWidth		= d_left->getWidth();
	float rightWidth	= d_right->getWidth();
	float midWidth		= absrect.getWidth() - leftWidth - rightWidth;

	Vector3 pos(absrect.d_left, absrect.d_top, z);
	Size	sz(leftWidth, absrect.getHeight());

	// left end
	d_left->draw(pos, sz, clipper, colours);

	// stretchy middle segment
	pos.d_x += sz.d_width;
	sz.d_width = midWidth;
	d_middle->draw(pos, sz, clipper, colours);

	// right end
	pos.d_x += sz.d_width;
	sz.d_width = rightWidth;
	d_right->draw(pos, sz, clipper, colours);


	//
	// Required preliminary work for main rendering operations
	//
	// Create a 'masked' version of the string if needed.
	String editText;

	if (isTextMasked())
	{
		editText.insert(0, d_text.length(), getMaskCodePoint());
	}
	else
	{
		editText = d_text;
	}

	// calculate new area rect considering text padding value.
	float textpadding = getTextPaddingPixels();

	absrect.d_left		+= textpadding;
	absrect.d_top		+= textpadding;
	absrect.d_right		-= textpadding;
	absrect.d_bottom	-= textpadding;

	// calculate best position to render text to ensure carat is always visible
	float textOffset;
	float extentToCarat = fnt->getTextExtent(editText.substr(0, getCaratIndex()));

	// if box is inactive
	if (!hasFocus)
	{
		textOffset = d_lastTextOffset;
	}
	// if carat is to the left of the box
	else if ((d_lastTextOffset + extentToCarat) < 0)
	{
		textOffset = -extentToCarat;
	}
	// if carat is off to the right.
	else if ((d_lastTextOffset + extentToCarat) >= (absrect.getWidth() - d_carat->getWidth()))
	{
		textOffset = absrect.getWidth() - extentToCarat - d_carat->getWidth();
	}
	// else carat is already within the box
	else
	{
		textOffset = d_lastTextOffset;
	}

	// adjust clipper for new target area
	clipper = absrect.getIntersection(clipper);


	//
	// Render carat
	//
	if ((!isReadOnly()) && hasFocus)
	{
		Vector3 pos(absrect.d_left + textOffset + extentToCarat, absrect.d_top, renderer->getZLayer(CaratLayer));
		Size	sz(d_carat->getWidth(), absrect.getHeight());
		d_carat->draw(pos, sz, clipper, colours);
	}

	//
	// Draw label text
	//
	// setup initial rect for text formatting
	Rect text_rect(absrect);
	text_rect.d_top  += (text_rect.getHeight() - getFont()->getLineSpacing()) * 0.5f;
	text_rect.d_left += textOffset;

	// draw pre-highlight text
	String sect = editText.substr(0, getSelectionStartIndex());
	colours.d_top_left = colours.d_top_right = colours.d_bottom_left = colours.d_bottom_right = (d_normalTextColour | alpha_comp);
	fnt->drawText(sect, text_rect, renderer->getZLayer(TextLayer), clipper, LeftAligned, colours);

	text_rect.d_left += fnt->getTextExtent(sect);

	// draw highlight text
	sect = editText.substr(getSelectionStartIndex(), getSelectionLength());
	colours.d_top_left = colours.d_top_right = colours.d_bottom_left = colours.d_bottom_right = (d_selectTextColour | alpha_comp);
	fnt->drawText(sect, text_rect, renderer->getZLayer(TextLayer), clipper, LeftAligned, colours);

	text_rect.d_left += fnt->getTextExtent(sect);

	// draw post-highlight text
	sect = editText.substr(getSelectionEndIndex());
	colours.d_top_left = colours.d_top_right = colours.d_bottom_left = colours.d_bottom_right = (d_normalTextColour | alpha_comp);
	fnt->drawText(sect, text_rect, renderer->getZLayer(TextLayer), clipper, LeftAligned, colours);


	//
	// Render selection brush
	//
	if (getSelectionLength() != 0)
	{
		// calculate required start and end offsets
		float selStartOffset	= fnt->getTextExtent(editText.substr(0, getSelectionStartIndex()));
		float selEndOffset		= fnt->getTextExtent(editText.substr(0, getSelectionEndIndex()));

		// setup colours
		if (hasFocus && (!isReadOnly()))
		{
			colours.d_top_left = colours.d_top_right = colours.d_bottom_left = colours.d_bottom_right = (d_selectBrushColour | alpha_comp);
		}
		else
		{
			colours.d_top_left = colours.d_top_right = colours.d_bottom_left = colours.d_bottom_right = (d_inactiveSelectBrushColour | alpha_comp);
		}

		// calculate highlight area
		Rect hlarea;
		hlarea.d_left	= absrect.d_left + textOffset + selStartOffset;
		hlarea.d_right	= absrect.d_left + textOffset + selEndOffset;
		hlarea.d_top	= text_rect.d_top;
		hlarea.d_bottom = hlarea.d_top + fnt->getLineSpacing();

		// render the highlight
		d_selection->draw(hlarea, renderer->getZLayer(SelectionLayer), clipper, colours);
	}

	d_lastTextOffset = textOffset;
}


//////////////////////////////////////////////////////////////////////////
/*************************************************************************

	Factory Methods

*************************************************************************/
//////////////////////////////////////////////////////////////////////////
/*************************************************************************
	Create, initialise and return a TLEditbox
*************************************************************************/
Window* TLEditboxFactory::createWindow(const String& name)
{
	TLEditbox* wnd = new TLEditbox(d_type, name);
	wnd->initialise();

	return wnd;
}

} // End of  CEGUI namespace section