// This file has been generated by Py++.

#include "boost/python.hpp"
#include "generators/include/python_CEGUI.h"
#include "PropertySet.pypp.hpp"

namespace bp = boost::python;

void register_PropertySet_class(){

    { //::CEGUI::PropertySet
        typedef bp::class_< CEGUI::PropertySet, bp::bases< CEGUI::PropertyReceiver > > PropertySet_exposer_t;
        PropertySet_exposer_t PropertySet_exposer = PropertySet_exposer_t( "PropertySet", "*!\n\
        \n\
           Class that contains a collection of Property objects.\n\
        *\n", bp::init< >("*!\n\
        \n\
           Constructs a new PropertySet object\n\
        *\n") );
        bp::scope PropertySet_scope( PropertySet_exposer );
        { //::CEGUI::PropertySet::addProperty
        
            typedef void ( ::CEGUI::PropertySet::*addProperty_function_type )( ::CEGUI::Property * ) ;
            
            PropertySet_exposer.def( 
                "addProperty"
                , addProperty_function_type( &::CEGUI::PropertySet::addProperty )
                , ( bp::arg("property") )
                , "*!\n\
               \n\
                  Adds a new Property to the PropertySet\n\
            \n\
               @param property\n\
                  Pointer to the Property object to be added to the PropertySet.\n\
            \n\
               @return\n\
                  Nothing.\n\
            \n\
               @exception NullObjectException      Thrown if  property is NULL.\n\
               @exception AlreadyExistsException   Thrown if a Property with the same name as  property already\
               exists in the PropertySet\n\
               *\n" );
        
        }
        { //::CEGUI::PropertySet::clearProperties
        
            typedef void ( ::CEGUI::PropertySet::*clearProperties_function_type )(  ) ;
            
            PropertySet_exposer.def( 
                "clearProperties"
                , clearProperties_function_type( &::CEGUI::PropertySet::clearProperties )
                , "*!\n\
               \n\
                  Removes all Property objects from the PropertySet.\n\
            \n\
               @return\n\
                  Nothing.\n\
               *\n" );
        
        }
        { //::CEGUI::PropertySet::getProperty
        
            typedef ::CEGUI::String ( ::CEGUI::PropertySet::*getProperty_function_type )( ::CEGUI::String const & ) const;
            
            PropertySet_exposer.def( 
                "getProperty"
                , getProperty_function_type( &::CEGUI::PropertySet::getProperty )
                , ( bp::arg("name") )
                , "*!\n\
               \n\
                  Gets the current value of the specified Property.\n\
            \n\
               @param name\n\
                  String containing the name of the Property who's value is to be returned.\n\
            \n\
               @return\n\
                  String object containing a textual representation of the requested Property.\n\
            \n\
               @exception UnknownObjectException   Thrown if no Property named  name is in the PropertySet.\n\
               *\n" );
        
        }
        { //::CEGUI::PropertySet::getPropertyDefault
        
            typedef ::CEGUI::String ( ::CEGUI::PropertySet::*getPropertyDefault_function_type )( ::CEGUI::String const & ) const;
            
            PropertySet_exposer.def( 
                "getPropertyDefault"
                , getPropertyDefault_function_type( &::CEGUI::PropertySet::getPropertyDefault )
                , ( bp::arg("name") )
                , "*!\n\
               \n\
                  Returns the default value of a Property as a String.\n\
            \n\
               @param name\n\
                  String containing the name of the Property who's default string is to be returned.\n\
            \n\
               @return\n\
                  String object containing a textual representation of the default value for this property.\n\
               *\n" );
        
        }
        { //::CEGUI::PropertySet::getPropertyHelp
        
            typedef ::CEGUI::String const & ( ::CEGUI::PropertySet::*getPropertyHelp_function_type )( ::CEGUI::String const & ) const;
            
            PropertySet_exposer.def( 
                "getPropertyHelp"
                , getPropertyHelp_function_type( &::CEGUI::PropertySet::getPropertyHelp )
                , ( bp::arg("name") )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "*!\n\
               \n\
                  Return the help text for the specified Property.\n\
            \n\
               @param name\n\
                  String holding the name of the Property who's help text is to be returned.\n\
            \n\
               @return\n\
                  String object containing the help text for the Property  name.\n\
            \n\
               @exception UnknownObjectException   Thrown if no Property named  name is in the PropertySet.\n\
               *\n" );
        
        }
        { //::CEGUI::PropertySet::getPropertyInstance
        
            typedef ::CEGUI::Property * ( ::CEGUI::PropertySet::*getPropertyInstance_function_type )( ::CEGUI::String const & ) const;
            
            PropertySet_exposer.def( 
                "getPropertyInstance"
                , getPropertyInstance_function_type( &::CEGUI::PropertySet::getPropertyInstance )
                , ( bp::arg("name") )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Retrieves a property instance (that was previously added)\n\
            \n\
                @param name\n\
                    String containing the name of the Property to be retrieved. If Property  name is not in the\
                    set, exception is thrown.\n\
            \n\
                @return\n\
                    Pointer to the property instance\n\
                *\n" );
        
        }
        { //::CEGUI::PropertySet::getPropertyIterator
        
            typedef ::CEGUI::ConstMapIterator< std::map<CEGUI::String, CEGUI::Property*, CEGUI::StringFastLessCompare, std::allocator<std::pair<CEGUI::String const, CEGUI::Property*> > > > ( ::CEGUI::PropertySet::*getPropertyIterator_function_type )(  ) const;
            
            PropertySet_exposer.def( 
                "getPropertyIterator"
                , getPropertyIterator_function_type( &::CEGUI::PropertySet::getPropertyIterator )
                , "*!\n\
            \n\
                Return a PropertySet.PropertyIterator object to iterate over the available\n\
                Properties.\n\
            *\n" );
        
        }
        { //::CEGUI::PropertySet::isPropertyDefault
        
            typedef bool ( ::CEGUI::PropertySet::*isPropertyDefault_function_type )( ::CEGUI::String const & ) const;
            
            PropertySet_exposer.def( 
                "isPropertyDefault"
                , isPropertyDefault_function_type( &::CEGUI::PropertySet::isPropertyDefault )
                , ( bp::arg("name") )
                , "*!\n\
               \n\
                  Returns whether a Property is at it's default value.\n\
            \n\
               @param name\n\
                  String containing the name of the Property who's default state is to be tested.\n\
            \n\
               @return\n\
                  - true if the property has it's default value.\n\
                  - false if the property has been modified from it's default value.\n\
               *\n" );
        
        }
        { //::CEGUI::PropertySet::isPropertyPresent
        
            typedef bool ( ::CEGUI::PropertySet::*isPropertyPresent_function_type )( ::CEGUI::String const & ) const;
            
            PropertySet_exposer.def( 
                "isPropertyPresent"
                , isPropertyPresent_function_type( &::CEGUI::PropertySet::isPropertyPresent )
                , ( bp::arg("name") )
                , "*!\n\
               \n\
                  Checks to see if a Property with the given name is in the PropertySet\n\
            \n\
               @param name\n\
                  String containing the name of the Property to check for.\n\
            \n\
               @return\n\
                  true if a Property named  name is in the PropertySet.  false if no Property named  name is in\
                  the PropertySet.\n\
               *\n" );
        
        }
        { //::CEGUI::PropertySet::removeProperty
        
            typedef void ( ::CEGUI::PropertySet::*removeProperty_function_type )( ::CEGUI::String const & ) ;
            
            PropertySet_exposer.def( 
                "removeProperty"
                , removeProperty_function_type( &::CEGUI::PropertySet::removeProperty )
                , ( bp::arg("name") )
                , "*!\n\
               \n\
                  Removes a Property from the PropertySet.\n\
            \n\
               @param name\n\
                  String containing the name of the Property to be removed.  If Property  name is not in the\
                  set, nothing happens.\n\
            \n\
               @return\n\
                  Nothing.\n\
               *\n" );
        
        }
        { //::CEGUI::PropertySet::setProperty
        
            typedef void ( ::CEGUI::PropertySet::*setProperty_function_type )( ::CEGUI::String const &,::CEGUI::String const & ) ;
            
            PropertySet_exposer.def( 
                "setProperty"
                , setProperty_function_type( &::CEGUI::PropertySet::setProperty )
                , ( bp::arg("name"), bp::arg("value") )
                , "*!\n\
               \n\
                  Sets the current value of a Property.\n\
            \n\
               @param name\n\
                  String containing the name of the Property who's value is to be set.\n\
            \n\
               @param value\n\
                  String containing a textual representation of the new value for the Property\n\
            \n\
               @return\n\
                  Nothing\n\
            \n\
               @exception UnknownObjectException   Thrown if no Property named  name is in the PropertySet.\n\
               @exception InvalidRequestException  Thrown when the Property was unable to interpret the content\
               of  value.\n\
               *\n" );
        
        }
    }

}
