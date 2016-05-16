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
using namespace std;
//
// OpenGL frame buffer configuration utilities.
//
struct GLConfigUtil{
  static void print_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig,
                              const char* attrib_str,
                              int attrib,
                              bool is_boolean);

  static void examine_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig);
};
//
// Print a configuration attribute.
//
void GLConfigUtil::print_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig,const char* attrib_str,int attrib,bool is_boolean){
  int value;

  if (glconfig->get_attrib(attrib, value))
    {
      std::cout << attrib_str << " = ";
      if (is_boolean)
        std::cout << (value == true ? "true" : "false") << std::endl;
      else
        std::cout << value << std::endl;
    }
  else
    {
      std::cout << "*** Cannot get "
                << attrib_str
                << " attribute value\n";
    }
}
//
// Print configuration attributes.
//
void GLConfigUtil::examine_gl_attrib(const Glib::RefPtr<const Gdk::GL::Config>& glconfig){
  std::cout << "\nOpenGL visual configurations :\n\n";

  std::cout << "glconfig->is_rgba() = "
            << (glconfig->is_rgba() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->is_double_buffered() = "
            << (glconfig->is_double_buffered() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->is_stereo() = "
            << (glconfig->is_stereo() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->has_alpha() = "
            << (glconfig->has_alpha() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->has_depth_buffer() = "
            << (glconfig->has_depth_buffer() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->has_stencil_buffer() = "
            << (glconfig->has_stencil_buffer() ? "true" : "false")
            << std::endl;
  std::cout << "glconfig->has_accum_buffer() = "
            << (glconfig->has_accum_buffer() ? "true" : "false")
            << std::endl;

  std::cout << std::endl;

  print_gl_attrib(glconfig, "Gdk::GL::USE_GL",           Gdk::GL::USE_GL,           true);
  print_gl_attrib(glconfig, "Gdk::GL::BUFFER_SIZE",      Gdk::GL::BUFFER_SIZE,      false);
  print_gl_attrib(glconfig, "Gdk::GL::LEVEL",            Gdk::GL::LEVEL,            false);
  print_gl_attrib(glconfig, "Gdk::GL::RGBA",             Gdk::GL::RGBA,             true);
  print_gl_attrib(glconfig, "Gdk::GL::DOUBLEBUFFER",     Gdk::GL::DOUBLEBUFFER,     true);
  print_gl_attrib(glconfig, "Gdk::GL::STEREO",           Gdk::GL::STEREO,           true);
  print_gl_attrib(glconfig, "Gdk::GL::AUX_BUFFERS",      Gdk::GL::AUX_BUFFERS,      false);
  print_gl_attrib(glconfig, "Gdk::GL::RED_SIZE",         Gdk::GL::RED_SIZE,         false);
  print_gl_attrib(glconfig, "Gdk::GL::GREEN_SIZE",       Gdk::GL::GREEN_SIZE,       false);
  print_gl_attrib(glconfig, "Gdk::GL::BLUE_SIZE",        Gdk::GL::BLUE_SIZE,        false);
  print_gl_attrib(glconfig, "Gdk::GL::ALPHA_SIZE",       Gdk::GL::ALPHA_SIZE,       false);
  print_gl_attrib(glconfig, "Gdk::GL::DEPTH_SIZE",       Gdk::GL::DEPTH_SIZE,       false);
  print_gl_attrib(glconfig, "Gdk::GL::STENCIL_SIZE",     Gdk::GL::STENCIL_SIZE,     false);
  print_gl_attrib(glconfig, "Gdk::GL::ACCUM_RED_SIZE",   Gdk::GL::ACCUM_RED_SIZE,   false);
  print_gl_attrib(glconfig, "Gdk::GL::ACCUM_GREEN_SIZE", Gdk::GL::ACCUM_GREEN_SIZE, false);
  print_gl_attrib(glconfig, "Gdk::GL::ACCUM_BLUE_SIZE",  Gdk::GL::ACCUM_BLUE_SIZE,  false);
  print_gl_attrib(glconfig, "Gdk::GL::ACCUM_ALPHA_SIZE", Gdk::GL::ACCUM_ALPHA_SIZE, false);

  std::cout << std::endl;
}

void GLWindow::init(){
    mesh_ptr = 0;
    mousex = 0;
    mousey = 0;
    view_sphere[0] =0.0f; view_sphere[1] = 0.0f; view_sphere[2] = 0.0f; view_sphere[3] = 0.0f;
    cam_pos[0] =0.0f; cam_pos[1] = 0.0f; cam_pos[2] = 5.0f; cam_pos[3] = 0.0f;
    render_scale = 1.0;

    float factor = 10.0f;
    vlight0[0] =    0.0f;     vlight0[1] = 0.0f;    vlight0[2] = 0.0f;
    vlight1[0] =    -factor;    vlight1[1] = factor;    vlight1[2] = factor;
    vlight2[0] =        0.0;    vlight2[1] = factor;    vlight2[2] = -factor;
}

GLWindow::GLWindow(BaseObjectType* baseObject, Glib::RefPtr<Gtk::Builder>& refBuilder):Gtk::DrawingArea(baseObject){
    //
    // Configure OpenGL-capable visual.
    //
    this->init();
    Glib::RefPtr<Gdk::GL::Config> glconfig;

    // Try double-buffered visual
    glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGBA | Gdk::GL::MODE_DEPTH | Gdk::GL::MODE_DOUBLE);
    if (!glconfig){
        std::cerr << "*** Cannot find the double-buffered visual.\n" << "*** Trying single-buffered visual.\n";
        // Try single-buffered visual
        glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGBA | Gdk::GL::MODE_DEPTH);
        if (!glconfig){
          std::cerr << "*** Cannot find any OpenGL-capable visual.\n";
          std::exit(1);
        }
    }
    // print frame buffer attributes.
    //GLConfigUtil::examine_gl_attrib(glconfig);

    // Set OpenGL-capability to the widget.
    set_gl_capability(glconfig);

    //Eventos para mover el modelo.
    add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON3_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::VISIBILITY_NOTIFY_MASK);
    signal_motion_notify_event().connect(sigc::mem_fun(*this, &GLWindow::on_motion_notify_event));
    signal_button_press_event().connect(sigc::mem_fun(*this, &GLWindow::on_button_press_event) );
}

GLWindow::~GLWindow(){
}


void GLWindow::set_mesh_pointer(Mesh *m){
    this->mesh_ptr = m;
}


void GLWindow::set_camera_from_mesh_pointer(){

    if(this->mesh_ptr){

        this->view_sphere[0] = mesh_ptr->get_bsphere_x();
        this->view_sphere[1] = mesh_ptr->get_bsphere_y();
        this->view_sphere[2] = mesh_ptr->get_bsphere_z();
        this->view_sphere[3] = mesh_ptr->get_bsphere_r();

        float zNear = 0.01f;
        float zFar = zNear+(30.0f*view_sphere[3]);
        float aspectRatio=(float)get_width()/(float)get_height();
        float anguloCamara=45.0f;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(anguloCamara, aspectRatio, zNear, zFar);

        this->cam_radius    = 15.0f * view_sphere[3];
        this->cam_theta     = 1.5f * M_PI;
        this->cam_phi       = 0.3f * M_PI;

		cam_pos[0] = view_sphere[0] + cam_radius*cos(cam_theta)*sin(cam_phi);
		cam_pos[1] = view_sphere[1] + cam_radius*sin(cam_theta)*sin(cam_phi) + 2.0f;
		cam_pos[2] = view_sphere[2] + cam_radius*cos(cam_phi);
		cam_pos[3] = 1.0f;

        this->redraw();
    }
}

void GLWindow::on_realize(){

    // We need to call the base on_realize()
    Gtk::DrawingArea::on_realize();
    Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();

    // GL calls.
    // *** OpenGL BEGIN ***
    if (!glwindow->gl_begin(get_gl_context()))
        return;

    glLightfv(GL_LIGHT0, GL_POSITION, vlight0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);

    glViewport(0, 0, get_width(), get_height());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, 1.0, 1.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 8.0, 8.0,    0.0, 1.0f, 0.0,  0.0, 1.0, 0.0);
    glwindow->gl_end();
    start_glew();
    // *** OpenGL END ***
}

bool GLWindow::on_configure_event(GdkEventConfigure* event){
  // Get GL::Window.
  Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
  // GL calls.
  // *** OpenGL BEGIN ***
  if (!glwindow->gl_begin(get_gl_context()))
    return false;

  glViewport(0, 0, get_width(), get_height());
  glwindow->gl_end();
  // *** OpenGL END ***

  return true;
}

bool GLWindow::on_expose_event(GdkEventExpose* event){
	//printf("Tiuque::render --- ");
	// Get GL::Window.
	Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
	// GL calls.
	// *** OpenGL BEGIN ***
	if (!glwindow->gl_begin(get_gl_context()))
	return false;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// position camera
	gluLookAt(  cam_pos[0],      cam_pos[1],      cam_pos[2], view_sphere[0],  view_sphere[1]+5.0f,  view_sphere[2], 0.0,            0.0,            1.0);
    //gluLookAt(  cam_pos[0], 2.0f, cam_pos[2], view_sphere[0],  view_sphere[1]+5.0f,  view_sphere[2], 0.0,            0.0,            1.0);

	// rotation for camera system
	glRotatef(90, 1.0f, 0.0f, 0.0f);

	// scale all scene
	glScalef(render_scale, render_scale, render_scale);

	// render
	glPushMatrix();
		if( mesh_ptr )
		    mesh_ptr->extern_render_mesh();
	glPopMatrix();
	// Swap buffers.
	if (glwindow->is_double_buffered())
		glwindow->swap_buffers();
	else
		glFlush();

	glwindow->gl_end();
	// *** OpenGL END ***
	//printf("ok\n");
	return true;
}

void GLWindow::redraw(){
    // force our program to redraw the entire clock.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win){
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return;
}


bool GLWindow::start_glew(){
    std::stringstream stream;
    GLenum initStatus = glewInit();
    if( initStatus != GLEW_OK ){
         printf( ">> GLEW Cannot Init\n");
         stream << "GLEW No puede Iniciar..." << std::endl;
         cout << stream.str() << std::endl;
         return false;
    }
    else{
         stream << "GLEW:" << std::endl <<
                  "\tInitializing.....................OK" << std::endl;
    }
    if( GLEW_ARB_vertex_buffer_object  ){
        stream << "\tGLEW_ARB_vertex_buffer_object....OK" << std::endl;
    }
    else{
        stream << "\tGLEW_ARB_vertex_buffer_object....FAILED" << std::endl;
         cout << stream.str() << std::endl;
    }
    stream <<     "\tOpenGL Version..................."<< glGetString(GL_VERSION) << std::endl;
    stream <<     "\tGLEW Support GL_VERSION_2_1......";
    if (! glewIsSupported("GL_VERSION_2_1")) {
        stream << "\tERROR: Support for necessary OpenGL extensions missing." << std::endl;
         cout << stream.str() << std::endl;
        return false;
    }
    else{
        stream << "OK" << std::endl;
    }
     cout << stream.str() << std::endl;
    return true;
}

bool GLWindow::on_motion_notify_event(GdkEventMotion* event){

	if (event->state & GDK_BUTTON3_MASK){
	    float soft_zoom_factor = sqrt(pow(cam_pos[0], 2) + pow(cam_pos[1], 2) + pow(cam_pos[2], 2))/view_sphere[3];
	    //printf("soft_zoom_factor = %f\n", soft_zoom_factor);
		this->cam_radius=this->cam_radius + 20*(event->y - this->mousey)/this->get_height()*soft_zoom_factor;
		if (this->cam_radius < 0)
			this->cam_radius=0;
	}
	else if (event->state & GDK_BUTTON1_MASK){
		this->cam_theta = this->cam_theta - (event->x - this->mousex)/this->get_width()*5;
		this->cam_phi   = this->cam_phi - (event->y - this->mousey)/this->get_height()*5;
		if (this->cam_phi >= M_PI)
			this->cam_phi = M_PI-0.000001f;
		else if (this->cam_phi <= 0)
			this->cam_phi = 0.000001f;
	}
	cam_pos[0] = view_sphere[0] + cam_radius*cos(cam_theta)*sin(cam_phi);
	cam_pos[1] = view_sphere[1] + cam_radius*sin(cam_theta)*sin(cam_phi);
	cam_pos[2] = view_sphere[2] + cam_radius*cos(cam_phi) + 10.0f;
	cam_pos[3] = 1.0f;
	this->redraw();
	this->mousex = event->x;
	this->mousey = event->y;
	return false;
}

bool GLWindow::on_button_press_event(GdkEventButton* event){
	this->mousex=event->x;
	this->mousey=event->y;
	return true;
}

