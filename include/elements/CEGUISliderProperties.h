/************************************************************************
	filename: 	CEGUISliderProperties.h
	created:	10/7/2004
	author:		Paul D Turner
	
	purpose:	Interface to properties for Slider class
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
#ifndef _CEGUISliderProperties_h_
#define _CEGUISliderProperties_h_

#include "CEGUIProperty.h"


// Start of CEGUI namespace section
namespace CEGUI
{

// Start of SliderProperties namespace section
/*!
\brief
	Namespace containing all classes that make up the properties interface for the Slider class
*/
namespace SliderProperties
{
/*!
\brief
	Property to access the current value of the slider.

	\par Usage:
		- Name: CurrentValue
		- Format: "[float]".

	\par Where:
		- [float] represents the current value of the slider.
*/
class CurrentValue : public Property
{
public:
	CurrentValue() : Property((utf8*)"CurrentValue", (utf8*)"Property to get/set the current value of the slider.  Value is a float.") {}

	String	get(const void* receiver) const;
	void	set(void* receiver, const String& value);
};


/*!
\brief
	Property to access the maximum value of the slider.

	\par Usage:
		- Name: MaximumValue
		- Format: "[float]".

	\par Where:
		- [float] represents the maximum value of the slider.
*/
class MaximumValue : public Property
{
public:
	MaximumValue() : Property((utf8*)"MaximumValue", (utf8*)"Property to get/set the maximum value of the slider.  Value is a float.") {}

	String	get(const void* receiver) const;
	void	set(void* receiver, const String& value);
};


/*!
\brief
	Property to access the click-step size for the slider.

	\par Usage:
		- Name: ClickStepSize
		- Format: "[float]".

	\par Where:
		- [float] represents the click-step size slider (this is how much the value changes when the slider container is clicked).
*/
class ClickStepSize : public Property
{
public:
	ClickStepSize() : Property((utf8*)"ClickStepSize", (utf8*)"Property to get/set the click-step size for the slider.  Value is a float.") {}

	String	get(const void* receiver) const;
	void	set(void* receiver, const String& value);
};

} // End of  SliderProperties namespace section

} // End of  CEGUI namespace section


#endif	// end of guard _CEGUISliderProperties_h_