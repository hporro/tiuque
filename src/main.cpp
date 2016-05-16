//////////////////////////////////////////////////////////////////////////////////
//                                                                           	//
//	tiuque                                                                  //
//	A 3D mesh manipulator software.	        				//
//                                                                           	//
//////////////////////////////////////////////////////////////////////////////////
//										//
//	Copyright © 2011 Cristobal A. Navarro.					//
//										//	
//	This file is part of tiuque.						//
//	tiuque is free software: you can redistribute it and/or modify		//
//	it under the terms of the GNU General Public License as published by	//
//	the Free Software Foundation, either version 3 of the License, or	//
//	(at your option) any later version.					//
//										//
//	tiuque is distributed in the hope that it will be useful,		//
//	but WITHOUT ANY WARRANTY; without even the implied warranty of		//
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	    	//
//	GNU General Public License for more details.				//
//										//
//	You should have received a copy of the GNU General Public License	//
//	along with tiuque.  If not, see <http://www.gnu.org/licenses/>. 	//
//										//
//////////////////////////////////////////////////////////////////////////////////


#include "Application.h"
#include "globals.h"

int main (int argc, char **argv)
{
  Gtk::Main kit(argc, argv);
  Gtk::GL::init(argc, argv);
  //
  // Query OpenGL extension version.
  //
  int major, minor;
  Gdk::GL::query_version(major, minor);
  std::cout << "Tiuque::glx version::"<< major << "." << minor << std::endl;
  //Load the GtkBuilder file and instantiate its widgets:
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try{
    refBuilder->add_from_file("tiuque.glade");
  }
  catch(const Glib::FileError& ex){
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex){
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }
  #else
      std::auto_ptr<Glib::Error> error;

      if (!refBuilder->add_from_file("tiuque.glade", error)){
        std::cerr << error->what() << std::endl;
        return 1;
      }
  #endif /* !GLIBMM_EXCEPTIONS_ENABLED */

  //Get the GtkBuilder-instantiated Dialog:
  Application* myApp;
  refBuilder->get_widget_derived("application", myApp);
  if(myApp){
    myApp->init();
    kit.run(*myApp);
  }
  return 0;
}
