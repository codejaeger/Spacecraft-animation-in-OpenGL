#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <bits/stdc++.h>

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3, *node4, *node5, *curr_node;

const int num_vertices = 100000;
const int num_vertices2 = 200000;
extern int cyl1_idx, con1_idx, cyl2_idx, cyl3_idx, prop_idx;

extern glm::vec4 v_positions_cyl1[num_vertices];
extern glm::vec4 v_colors_cyl1[num_vertices];
extern glm::vec4 v_normals_cyl1[num_vertices];
extern glm::vec2 tex_coords_cyl1[num_vertices];

// int con1_idx = 0;
extern glm::vec4 v_positions_con1[num_vertices];
extern glm::vec4 v_colors_con1[num_vertices];
extern glm::vec4 v_normals_con1[num_vertices];
extern glm::vec2 tex_coords_con1[num_vertices];

// int cyl2_idx = 0;
extern glm::vec4 v_positions_cyl2[num_vertices];
extern glm::vec4 v_colors_cyl2[num_vertices];
extern glm::vec4 v_normals_cyl2[num_vertices];
extern glm::vec2 tex_coords_cyl2[num_vertices];

// int cyl3_idx = 0;
extern glm::vec4 v_positions_cyl3[num_vertices];
extern glm::vec4 v_colors_cyl3[num_vertices];
extern glm::vec4 v_normals_cyl3[num_vertices];
extern glm::vec2 tex_coords_cyl3[num_vertices];

// int prop_idx = 0;

extern glm::vec4 v_positions_prop[num_vertices2];
extern glm::vec4 v_colors_prop[num_vertices2];
extern glm::vec4 v_normals_prop[num_vertices2];
extern glm::vec2 tex_coords_prop[num_vertices2];

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
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      curr_node->dec_ry();
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
      curr_node->inc_ry();
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
      curr_node->dec_rx();
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
      curr_node->inc_rx();
    else if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
      curr_node->dec_rz();
    else if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
      curr_node->inc_rz();
    else if (key == GLFW_KEY_X && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
      curr_node->inc_x();
    else if (key == GLFW_KEY_X && action == GLFW_PRESS)
      curr_node->dec_x();
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      c_yrot -= 10.0;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      c_yrot += 10.0;
    else if (key == GLFW_KEY_W  && action == GLFW_PRESS)
      c_xrot -= 10.0;
    else if (key == GLFW_KEY_S  && action == GLFW_PRESS)
      c_xrot += 10.0;        
    else if (key == GLFW_KEY_Q  && action == GLFW_PRESS)
      c_zrot -= 10.0;
    else if (key == GLFW_KEY_E  && action == GLFW_PRESS)
      c_zrot += 10.0;
    else if (key == GLFW_KEY_K  && action == GLFW_PRESS){
      std::ofstream outfile;
      outfile.open("data/a3-model-2.raw");

      outfile<<cyl1_idx<<"\n";
      for(int i=0;i<cyl1_idx;i++){ // in lexicographic order
        // if(v_positions_cyl1[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_cyl1[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_cyl1[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_cyl1[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_cyl1[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile<<con1_idx<<"\n";
      for(int i=0;i<con1_idx;i++){
        // if(v_positions_con1[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_con1[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_con1[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_con1[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_con1[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile<<cyl2_idx<<"\n";
      for(int i=0;i<cyl2_idx;i++){
        // if(v_positions_cyl2[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_cyl2[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_cyl2[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_cyl2[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_cyl2[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile<<cyl3_idx<<"\n";
      for(int i=0;i<cyl3_idx;i++){
        // if(v_positions_cyl3[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_cyl3[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_cyl3[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_cyl3[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_cyl3[i][j]; // color
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

      outfile.close();
      std::cout<<"Model saved successfully\n";
    }
  }
};  
  


