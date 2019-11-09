#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <bits/stdc++.h>

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3, *node4, *node5, *curr_node;

const int num_vertices = 100000;
extern glm::vec4 v_positions_box[num_vertices], v_colors_box[num_vertices], v_normals_box[num_vertices];
extern glm::vec2 tex_coords_box[num_vertices];
extern glm::vec4 v_positions_prop[num_vertices], v_colors_prop[num_vertices], v_normals_prop[num_vertices];
extern glm::vec2 tex_coords_prop[num_vertices];
extern glm::vec4 v_positions_solar[num_vertices], v_colors_solar[num_vertices], v_normals_solar[num_vertices];
extern glm::vec2 tex_coords_solar[num_vertices];
extern glm::vec4 v_positions_refl[num_vertices], v_colors_refl[num_vertices], v_normals_refl[num_vertices];
extern glm::vec2 tex_coords_refl[num_vertices];
extern glm::vec4 v_positions_extra[num_vertices], v_colors_extra[num_vertices], v_normals_extra[num_vertices];
extern glm::vec2 tex_coords_extra[num_vertices];
extern int box_idx, prop_idx, solar_idx, refl_idx, extra_idx;

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
      curr_node = node5;
    else if (key == GLFW_KEY_LEFT){
      if(curr_node==node1) curr_node->dec_ry();
      else if(curr_node==node2 && node2->rz<90.0) curr_node->inc_rz();
      else if(curr_node==node3 && node3->ry<180.0 && node2->rz==90.0){
        node3->inc_ry();
        node4->inc_ry();
      }
      else if(curr_node==node5 && node5->rz<0.0) curr_node->inc_rz();
    }
    else if (key == GLFW_KEY_RIGHT){
      if(curr_node==node1) curr_node->inc_ry();
      else if(curr_node==node2 && node2->rz>0.0) curr_node->dec_rz();
      else if(curr_node==node3 && node3->ry>0.0){
        node3->dec_ry();
        node4->dec_ry();
      }
      else if(curr_node==node5 && node5->rz>-60.0) curr_node->dec_rz();
    }
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS){
      if(curr_node==node1) curr_node->dec_rx();
    }
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
      if(curr_node==node1) curr_node->inc_rx();
    }
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS){
      if(curr_node==node1) curr_node->dec_rz();
    }
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS){
      if(curr_node==node1) curr_node->inc_rz();
    }
    else if (key == GLFW_KEY_K  && action == GLFW_PRESS){
      std::ofstream outfile;
      outfile.open("data/a3-model-3.raw");

      outfile<<box_idx<<"\n";
      for(int i=0;i<box_idx;i++){ // in lexicographic order
        // if(v_positions_box[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_box[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_box[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_box[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_box[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile<<prop_idx<<"\n";
      for(int i=0;i<prop_idx;i++){
        // if(v_positions_prop[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_prop[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_prop[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_prop[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_prop[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile<<solar_idx<<"\n";
      for(int i=0;i<solar_idx;i++){
        // if(v_positions_solar[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_solar[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_solar[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_solar[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_solar[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile<<refl_idx<<"\n";
      for(int i=0;i<refl_idx;i++){
        // if(v_positions_refl[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_refl[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_refl[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_refl[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_refl[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile<<extra_idx<<"\n";
      for(int i=0;i<extra_idx;i++){
        // if(v_positions_extra[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_extra[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_extra[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_extra[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_extra[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile.close();
      std::cout<<"Model saved successfully\n";
    }
  }
};  
  


