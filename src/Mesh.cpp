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

#include "Mesh.h"
Mesh::Mesh() : accumflips(0){
    init();
}
Mesh::Mesh(cleap_mesh* m) : accumflips(0){
    init();
    this->my_cleap_mesh = m;
    n = cleap_get_vertex_count(m);
    vel = new hmath::float2[cleap_get_vertex_count(m)];
}
Mesh::Mesh(const char *filename) : accumflips(0){
    cleap_init();
    this->my_cleap_mesh = cleap_load_mesh(filename);
    this->default_filename = filename;
    n = cleap_get_vertex_count(this->my_cleap_mesh);
    vel = new hmath::float2[cleap_get_vertex_count(this->my_cleap_mesh)];
	float maxVel = 0.0025;
    for(int i=4;i<n;i++){
        vel[i]=hmath::float2{i*maxVel,i*maxVel};
    }
	
}
void Mesh::init(){
    this->my_cleap_mesh = 0;
    this->default_filename = 0;
    this->accumflips=0;
}
void Mesh::save_mesh(const char *filename){
    cleap_save_mesh(my_cleap_mesh, filename);
}
void Mesh::save_mesh_default(){
    if(this->default_filename)
        cleap_save_mesh(my_cleap_mesh, this->default_filename);
    else
        printf("Tiuque::save_mesh_default::cannot save... default_filename = NULL.");
}
void Mesh::extern_render_mesh(){
    cleap_render_mesh(my_cleap_mesh);
}
void Mesh::delaunay_transformation(int mode){
    cleap_delaunay_transformation(this->my_cleap_mesh, mode);
}
void Mesh::delaunay_transformation_interactive(int mode){
	int flips = cleap_delaunay_transformation_interactive(this->my_cleap_mesh, mode);
	accumflips += flips;
	printf("flips = %i       accumflips = %i\n", flips, accumflips);
}
void Mesh::print_mesh(){
	printf("CURRENT MESH:\n");
    cleap_print_mesh(my_cleap_mesh);
}
void Mesh::random_move_points(){
	GLuint p = cleap_get_vertex_buffer(this->my_cleap_mesh);
	glBindBuffer(GL_ARRAY_BUFFER, p);
	void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	hmath::float4 pos[n];
	memcpy(pos, ptr, sizeof(hmath::float4) * n);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	for (int i = 4; i < n; i++) {
		if (pos[i][1] < -0.5 || pos[i][1] > 0.5) {vel[i][1] *= -1;pos[i][1] += vel[i][1];}
		if (pos[i][0] < -0.5 || pos[i][0] > 0.5) {vel[i][0] *= -1;pos[i][0] += vel[i][0];}
		pos[i][0] += vel[i][0];
		pos[i][1] += vel[i][1];
	}

	glBindBuffer(GL_ARRAY_BUFFER, p);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hmath::float4) * n, pos, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);	
}
void Mesh::fix_triangles(){
    cleap_fix_inverted_triangles(my_cleap_mesh);
}
Mesh::~Mesh(){
    cleap_clear_mesh(my_cleap_mesh);
    this->my_cleap_mesh = 0;
}
