/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;

// Camera position and rotation Parameters
// 4.95 0.15 0.48
GLfloat c1_xpos = 4.9350, c1_ypos = 0.1425, c1_zpos = 0.4800;
GLfloat c1_up_x = 0.0, c1_up_y = 0.0, c1_up_z = 1.0;
GLfloat c1_xrot=0.0,c1_yrot=0.0,c1_zrot=0.0;

GLfloat c2_xpos = 5.0, c2_ypos = 1.05, c2_zpos = 1.01;
GLfloat c2_up_x = 0.0, c2_up_y = 1.0, c2_up_z = 0.0;
GLfloat c2_xrot=0.0,c2_yrot=0.0,c2_zrot=0.0;

GLfloat c3_xpos = 0.0, c3_ypos = 0.0, c3_zpos = 7.0;
GLfloat c3_up_x = 0.0, c3_up_y = 1.0, c3_up_z = 0.0;
GLfloat c3_xrot=0.0,c3_yrot=0.0,c3_zrot=0.0;

int camera = 1;
bool animation = false;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;
//Shader program attribs
GLuint vPosition,vColor,vNormal;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode* root_node;
csX75::HNode* curr_node;
csX75::HNode *node1, *node2, *node3, *node4, *node5, *node6, *node7, *node8, *node9, *node10, *node11, *node12,*node1e,*node2e,*node3e,*node4e,*node5e;
// csX75::HNode *bez_cnt[100],*bezir[10000];
csX75::HNode *node_line[4], *bez_node[4], *new_node;
// int bez_cnt_nodes=0,bez_nodes=0;
//-------------------------------------------------------------------------

#endif
