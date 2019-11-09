#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <bits/stdc++.h>

extern GLfloat c_xrot,c_yrot,c_zrot;
extern GLfloat c_xpos, c_ypos, c_zpos;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3, *node4, *node5, *curr_node;

const int num_vertices = 100000;
extern glm::vec4 v_positions_earth[num_vertices], v_colors_earth[num_vertices], v_normals_earth[num_vertices];
extern glm::vec2 tex_coords_earth[num_vertices];
extern glm::vec4 v_positions_space[num_vertices], v_colors_space[num_vertices], v_normals_space[num_vertices];
extern glm::vec2 tex_coords_space[num_vertices];
extern int earth_idx, space_idx;

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
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
      curr_node->inc_ry();//c_yrot += 5.0;
    else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
      curr_node->dec_ry();//c_yrot += 5.0;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
      curr_node->inc_rx();//c_yrot += 5.0;
    else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
      curr_node->dec_rx();//c_yrot += 5.0;
    else if (key == GLFW_KEY_RIGHT  && action == GLFW_PRESS)
      c_xpos += 0.2;
    else if (key == GLFW_KEY_LEFT  && action == GLFW_PRESS)
      c_xpos -= 0.2;
    else if (key == GLFW_KEY_UP  && action == GLFW_PRESS)
      c_ypos += 0.2;
    else if (key == GLFW_KEY_DOWN  && action == GLFW_PRESS)// && mods==GLFW_MOD_SHIFT
      c_ypos -= 0.2;
    else if (key == GLFW_KEY_RIGHT_BRACKET  && action == GLFW_PRESS)
      c_zpos += 0.1;
    else if (key == GLFW_KEY_LEFT_BRACKET  && action == GLFW_PRESS)
      c_zpos -= 0.1;
    else if (key == GLFW_KEY_K  && action == GLFW_PRESS){
      std::ofstream outfile;
      outfile.open("data/a3-model-0.raw");

      outfile<<earth_idx<<"\n";
      for(int i=0;i<earth_idx;i++){ // in lexicographic order
          for(int j=0;j<4;j++){
            outfile<<v_positions_earth[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_earth[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_earth[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_earth[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
      }

      outfile<<space_idx<<"\n";
      for(int i=0;i<space_idx;i++){
          for(int j=0;j<4;j++){
            outfile<<v_positions_space[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_space[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_space[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_space[i][j]; // color
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
  


