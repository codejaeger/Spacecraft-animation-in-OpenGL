#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <bits/stdc++.h>

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern csX75::HNode* node1, *node2, *node3, *node4, *node5, *curr_node;

const int num_vertices = 100000;
extern int box_idx, plat_idx, w1_idx, w2_idx, w3_idx;
extern glm::vec4 v_positions_box[num_vertices], v_colors_box[num_vertices], v_normals_box[num_vertices];
// extern glm::vec2 tex_coords_box[num_vertices];
extern glm::vec4 v_positions_plat[num_vertices], v_colors_plat[num_vertices], v_normals_plat[num_vertices];
// extern glm::vec2 tex_coords_plat[num_vertices];
extern glm::vec4 v_positions_w1[num_vertices], v_colors_w1[num_vertices], v_normals_w1[num_vertices];
extern glm::vec2 tex_coords_w1[num_vertices];
extern glm::vec4 v_positions_w2[num_vertices], v_colors_w2[num_vertices], v_normals_w2[num_vertices];
// extern glm::vec2 tex_coords_w2[num_vertices];
extern glm::vec4 v_positions_w3[num_vertices], v_colors_w3[num_vertices], v_normals_w3[num_vertices];
// extern glm::vec2 tex_coords_w3[num_vertices];

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
      curr_node = node3;
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS){
      if(curr_node==node1) curr_node->dec_ry();
      else curr_node->dec_x();
    }
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
      if(curr_node==node1) curr_node->inc_ry();
      else curr_node->inc_x();
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
      outfile.open("data/a3-model-1.raw");

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
          // for(int j=0;j<2;j++){
          //   outfile<<tex_coords_box[i][j]; // color
          //   outfile<<" ";
          // }
          outfile<<"\n";
        // }
      }

      outfile<<plat_idx<<"\n";
      for(int i=0;i<plat_idx;i++){
        // if(v_positions_plat[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_plat[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_plat[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_plat[i][j]; // color
            outfile<<" ";
          }
          // for(int j=0;j<2;j++){
          //   outfile<<tex_coords_plat[i][j]; // color
          //   outfile<<" ";
          // }
          outfile<<"\n";
        // }
      }

      outfile<<w1_idx<<"\n";
      for(int i=0;i<w1_idx;i++){
        // if(v_positions_w1[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_w1[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_w1[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_w1[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<2;j++){
            outfile<<tex_coords_w1[i][j]; // color
            outfile<<" ";
          }
          outfile<<"\n";
        // }
      }

      outfile<<w2_idx<<"\n";
      for(int i=0;i<w2_idx;i++){
        // if(v_positions_w2[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_w2[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_w2[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_w2[i][j]; // color
            outfile<<" ";
          }
          // for(int j=0;j<2;j++){
          //   outfile<<tex_coords_w2[i][j]; // color
          //   outfile<<" ";
          // }
          outfile<<"\n";
        // }
      }

      outfile<<w3_idx<<"\n";
      for(int i=0;i<w3_idx;i++){
        // if(v_positions_w3[i][3]==1.0){
          for(int j=0;j<4;j++){
            outfile<<v_positions_w3[i][j];
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_colors_w3[i][j]; // color
            outfile<<" ";
          }
          for(int j=0;j<4;j++){
            outfile<<v_normals_w3[i][j]; // color
            outfile<<" ";
          }
          // for(int j=0;j<2;j++){
          //   outfile<<tex_coords_w3[i][j]; // color
          //   outfile<<" ";
          // }
          outfile<<"\n";
        // }
      }

      outfile.close();
      std::cout<<"Model saved successfully\n";
    }
  }
};  
  


