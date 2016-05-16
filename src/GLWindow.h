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

#include "globals.h"
#include "Mesh.h"

class GLWindow : public Gtk::DrawingArea, public Gtk::GL::Widget<GLWindow>{

private:
    Mesh *mesh_ptr;
    float view_sphere[4], cam_pos[4];
    float cam_radius, cam_theta, cam_phi, render_scale;
    int mousex, mousey;
    // lights
    GLfloat vlight0[3];
    GLfloat vlight1[3];
    GLfloat vlight2[3];

public:
    GLWindow(BaseObjectType* baseObject, Glib::RefPtr<Gtk::Builder>& refBuilder);
    virtual ~GLWindow();
    void init();
    void redraw();
    bool start_glew();
    void set_mesh_pointer(Mesh *m);
    void set_camera_from_mesh_pointer();
    void set_render_scale(float rs){ this->render_scale = rs;}

protected:
    virtual void on_realize();
    virtual bool on_configure_event(GdkEventConfigure* event);
    virtual bool on_expose_event(GdkEventExpose* event);
    virtual bool on_motion_notify_event(GdkEventMotion* event);
    virtual bool on_button_press_event(GdkEventButton* event);
};
