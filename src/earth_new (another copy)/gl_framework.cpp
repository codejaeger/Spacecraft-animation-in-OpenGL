#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <bits/stdc++.h>

extern GLfloat c_xrot,c_yrot,c_zrot,c_xpos,c_zpos,c_ypos;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3,*node4,*node5,*curr_node;
extern int tri_idx , trii, tric, trimars , trisun;
const int num_vertices = 100000;
extern glm::vec4 v_positions[num_vertices], v_normals[num_vertices];
extern glm::vec4 spv_positions[num_vertices], spv_normals[num_vertices];
extern glm::vec4 cpv_positions[num_vertices], cpv_normals[num_vertices];
extern glm::vec4 sv_positions[num_vertices], sv_normals[num_vertices];
extern glm::vec4 mrsv_positions[num_vertices], mrsv_normals[num_vertices];
extern glm::vec3 tex_coords[num_vertices],cptex_coords[num_vertices],stex_coords[num_vertices],sptex_coords[num_vertices],mrstex_coords[num_vertices];
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      curr_node = node1;  
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
      curr_node = node2; 
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
      curr_node = node3; 
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
      curr_node = node4; 
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
      curr_node = node5;  
     else if (key == GLFW_KEY_LEFT_BRACKET)
    {
      c_zpos = c_zpos - 0.005;
    }
    else if (key == GLFW_KEY_RIGHT_BRACKET)
    {
      c_zpos = c_zpos + 0.005;
    }
    else if (key == GLFW_KEY_LEFT )
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT )
      curr_node->inc_ry();
    else if (key == GLFW_KEY_UP )
      curr_node->dec_rx();
    else if (key == GLFW_KEY_DOWN)
      curr_node->inc_rx();
    else if (key == GLFW_KEY_PAGE_UP)
      curr_node->change_rot(1,0.0,0.0);
    else if (key == GLFW_KEY_PAGE_DOWN)
      // curr_node->inc_rz();
      curr_node->change_rot(-1,0.0,0.0);
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A )
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D )
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W )
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S )
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q )
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E )
      c_zrot += 1.0;   
    else if (key == GLFW_KEY_K  && action == GLFW_PRESS){
      std::ofstream outfile;
      outfile.open("./a3-model-0.raw");

      outfile<<tri_idx<<"\n";
      for(int i=0;i<tri_idx;i++){ // in lexicographic order
          for(int j=0;j<4;j++){
            outfile<<v_positions[i][j];
            outfile<<" ";
          }
          // for(int j=0;j<4;j++){
          //   outfile<<v_colors_earth[i][j]; // color
          //   outfile<<" ";
          // }
          for(int j=0;j<4;j++){
            outfile<<v_normals[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<3;j++){
            outfile<<tex_coords[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
      }

      outfile<<trii<<"\n";
      for(int i=0;i<trii;i++){ // in lexicographic order
          for(int j=0;j<4;j++){
            outfile<<spv_positions[i][j];
            outfile<<" ";
          }
          // for(int j=0;j<4;j++){
          //   outfile<<v_colors_earth[i][j]; // color
          //   outfile<<" ";
          // }
          for(int j=0;j<4;j++){
            outfile<<spv_normals[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<3;j++){
            outfile<<sptex_coords[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
      }
      outfile<<tric<<"\n";
      for(int i=0;i<tric;i++){ // in lexicographic order
          for(int j=0;j<4;j++){
            outfile<<cpv_positions[i][j];
            outfile<<" ";
          }
          // for(int j=0;j<4;j++){
          //   outfile<<v_colors_earth[i][j]; // color
          //   outfile<<" ";
          // }
          for(int j=0;j<4;j++){
            outfile<<cpv_normals[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<3;j++){
            outfile<<cptex_coords[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
      }
      outfile<<trisun<<"\n";
      for(int i=0;i<trisun;i++){ // in lexicographic order
          for(int j=0;j<4;j++){
            outfile<<sv_positions[i][j];
            outfile<<" ";
          }
          // for(int j=0;j<4;j++){
          //   outfile<<v_colors_earth[i][j]; // color
          //   outfile<<" ";
          // }
          for(int j=0;j<4;j++){
            outfile<<sv_normals[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<3;j++){
            outfile<<stex_coords[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
      }
      outfile<<trimars<<"\n";
      for(int i=0;i<trimars;i++){ // in lexicographic order
          for(int j=0;j<4;j++){
            outfile<<mrsv_positions[i][j];
            outfile<<" ";
          }
          // for(int j=0;j<4;j++){
          //   outfile<<v_colors_earth[i][j]; // color
          //   outfile<<" ";
          // }
          for(int j=0;j<4;j++){
            outfile<<mrsv_normals[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<3;j++){
            outfile<<mrstex_coords[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
      }
      outfile.close();
      std::cout<<"Model saved successfully\n";
    }
    else if(key == GLFW_KEY_L  && action == GLFW_PRESS)
    {
      std::ifstream infile;
  infile.open("./a3-model-0.raw");
    infile>>tri_idx;
    // std::cout<<filename<<"\n";
  for(int i=0;i<tri_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions[i][j];
    // for(int j=0;j<4;j++) infile>>v_colors_earth[i][j];
    for(int j=0;j<4;j++) infile>>v_normals[i][j];
    for(int j=0;j<3;j++) infile>>tex_coords[i][j];
  }
    infile>>trii;
  for(int i=0;i<trii;i++){
    for(int j=0;j<4;j++) infile>>spv_positions[i][j];
    // for(int j=0;j<4;j++) infile>>v_colors_earth[i][j];
    for(int j=0;j<4;j++) infile>>spv_normals[i][j];
    for(int j=0;j<3;j++) infile>>sptex_coords[i][j];
  }
    infile>>tric;
  for(int i=0;i<tric;i++){
    for(int j=0;j<4;j++) infile>>cpv_positions[i][j];
    // for(int j=0;j<4;j++) infile>>v_colors_earth[i][j];
    for(int j=0;j<4;j++) infile>>cpv_normals[i][j];
    for(int j=0;j<3;j++) infile>>cptex_coords[i][j];
  }
    infile>>trisun;

  for(int i=0;i<trisun;i++){
    for(int j=0;j<4;j++) infile>>sv_positions[i][j];
    // for(int j=0;j<4;j++) infile>>v_colors_earth[i][j];
    for(int j=0;j<4;j++) infile>>sv_normals[i][j];
    for(int j=0;j<3;j++) infile>>stex_coords[i][j];
  }
  infile>>trimars;
  for(int i=0;i<trimars;i++){
    for(int j=0;j<4;j++) infile>>mrsv_positions[i][j];
    // for(int j=0;j<4;j++) infile>>v_colors_earth[i][j];
    for(int j=0;j<4;j++) infile>>mrsv_normals[i][j];
    for(int j=0;j<3;j++) infile>>mrstex_coords[i][j];
  }

  infile.close();
  std::cout<<"Model loaded successfully"<<"\n";

    }
  }
};  
  


