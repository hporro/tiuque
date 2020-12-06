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
#include "GLWindow.h"
#include "Mesh.h"
class Application : public Gtk::Window{

    private:
        GLWindow* my_gl_window;
        Mesh* myMesh;
        Glib::RefPtr<Gtk::Builder> ref_builder;
        //widget pointers
        Gtk::Button *button_exit, *button_mdt_2d, *button_mdt_3d, *button_clear, *button_fix_triangles, *button_move_particles, *button_print_mesh;
        Gtk::ToggleButton *toogle_button_wireframe, *toogle_button_solid;
        Gtk::CheckButton *check_button_educational_mode;
        Gtk::HScale *hscale_size;
        Gtk::ImageMenuItem *item_open, *item_save, *item_save_as, *item_help_about;
        Gtk::AboutDialog *about_dialog;

    public:
        Application(BaseObjectType* baseObject, Glib::RefPtr<Gtk::Builder>& refBuilder);
        virtual ~Application();
        void init();
        // load / save
        int load_mesh(const char* filename);
        int save_mesh(const char* filename);
        // signal handlers:
        void on_button_exit_clicked();
        void on_button_clear_clicked();
        void on_menu_file_open();
        void on_menu_file_save();
        void on_menu_file_save_as();
        void on_menu_file_quit();
        void on_menu_help_about();
        void on_button_delaunay_2d_clicked();
        void on_button_delaunay_3d_clicked();
        void on_toggle_button_wireframe_toggled();
        void on_toggle_button_solid_toggled();
        void on_check_button_educational_mode_toggled();
        void on_hscale_size_change_value();
        
        void on_button_fix_triangles_clicked();
        void on_button_move_particles_clicked();
        void on_button_print_mesh_clicked();
};
