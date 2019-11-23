#include "gl_framework.hpp"
#include "hierarchy_node.hpp"
#include <bits/stdc++.h>

extern GLfloat c1_xpos,c1_ypos,c1_zpos;
extern GLfloat c1_xrot,c1_yrot,c1_zrot;
extern GLfloat c2_xpos,c2_ypos,c2_zpos;
extern GLfloat c2_xrot,c2_yrot,c2_zrot;
extern int bez_ctrl_idx,bezier_idx;
extern bool enable_perspective;
extern int camera;
extern bool animation;
extern int sig;
extern int bez_idx;

extern csX75::HNode *node1, *node2, *node3,*node4, *node5, *node6, *node7, *node8, *node9, *node10, *node11,*node1e,*node2e,*node3e,*node4e,*node5e,*curr_node;

const int num_vertices = 100000;
extern glm::vec3 cur_cent;
extern glm::vec3 bez_ctrl[100];
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

  void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
  {
    // double xpos, ypos;
       //getting cursor position
    // glfwGetCursorPos(window, &xpos, &ypos);
    // std::cout << "Cursor Position at (" << xpos << " : " << ypos << '\n';
  }
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
    {
       double xpos, ypos;
       //getting cursor position
       glfwGetCursorPos(window, &xpos, &ypos);
       std::cout << "Cursor Position at (" << xpos << " : " << ypos << '\n';
    }
  }
  // glfwSetMouseButtonCallback(window, mouse_callback);
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
    // else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    //   curr_node = node4; 
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
      curr_node = node5;
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
      curr_node = node6;
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
      curr_node = node7;
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
      curr_node = node8;
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
      curr_node = node9;
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
      curr_node = node10;
    else if (key == GLFW_KEY_KP_1 && action == GLFW_PRESS)
      curr_node = node1e;
    else if (key == GLFW_KEY_KP_3 && action == GLFW_PRESS)
      curr_node = node2e;
    else if (key == GLFW_KEY_KP_5 && action == GLFW_PRESS)
      curr_node = node3e;
    else if (key == GLFW_KEY_KP_7 && action == GLFW_PRESS)
      curr_node = node4e;
    else if (key == GLFW_KEY_KP_9 && action == GLFW_PRESS)
      curr_node = node5e;
     else if(key == GLFW_KEY_P && action == GLFW_PRESS){
      //  std::cout<<"hello";
      bez_ctrl[bez_idx] = cur_cent;
      bez_idx++;
      sig = 1;
      // for(int i=0;i<bez_ctrl_idx;i++)
      // {
      //   glm::vec4 temp = glm::vec4(bez_ctrl[i],1.0);
      //   std::cout<<temp[0]<<" "<<temp[1]<<" "<<temp[2]<<" "<<temp[3]<<'\n';
      // }
      // update_curve();
      std::cout<<"Control point placed\n";
    }
    // else if (key == GLFW_KEY_P && action == GLFW_PRESS)
    //   enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_PAGE_UP)
      curr_node->change_rot(1);
    else if (key == GLFW_KEY_PAGE_DOWN)
      // curr_node->inc_rz();
      curr_node->change_rot(-1);
    else if (key == GLFW_KEY_A )
      if(camera==1)c1_yrot -= 1.0;
    else
      c2_yrot -= 1.0;
    else if (key == GLFW_KEY_D )
      if(camera==1)c1_yrot += 1.0;
    else
      c2_yrot += 1.0;
      // c1_yrot += 1.0;
    else if (key == GLFW_KEY_W )
      // c1_xrot -= 1.0;
      if(camera==1)c1_xrot -= 1.0;
    else
      c2_xrot -= 1.0;
    else if (key == GLFW_KEY_S )
      // c1_xrot += 1.0;
      if(camera==1)c1_xrot += 1.0;
    else
      c2_xrot += 1.0;        
    else if (key == GLFW_KEY_Q )
      // c1_zrot -= 1.0;
      if(camera==1)c1_zrot -= 1.0;
    else
      c2_zrot -= 1.0;
    else if (key == GLFW_KEY_E )
      // c1_zrot += 1.0;
      if(camera==1)c1_zrot += 1.0;
    else
      c2_zrot += 1.0;
    else if (key == GLFW_KEY_X){
      node2->tx -= 0.01;
      node2->ty -= 0.01;
      node5->tx -= 0.01;
      node5->ty -= 0.01;
      node2->update_matrices();
      node5->update_matrices();
    }
    // else if (key == GLFW_KEY_KP_8 )
    //   curr_node->dec_ry();
    // else if (key == GLFW_KEY_KP_2 )
    //   curr_node->inc_ry();
    // else if (key == GLFW_KEY_KP_4 )
    //   curr_node->dec_rx();
    // else if (key == GLFW_KEY_KP_6)
    //   curr_node->inc_rx();
    else if (key == GLFW_KEY_KP_8 )
      // curr_node->dec_ry();
    {
      cur_cent = cur_cent + glm::vec3(0.01,0.0,0.0);
      node4->tx+=0.01;
      node4->update_matrices();
    }
    else if (key == GLFW_KEY_KP_2 )
      // curr_node->inc_ry();
      {
        cur_cent = cur_cent + glm::vec3(-0.01,0.0,0.0);
        node4->tx-=0.01;
      node4->update_matrices();

      }
    else if (key == GLFW_KEY_KP_4 )
      // curr_node->dec_rx();
    {
      cur_cent = cur_cent + glm::vec3(0.0,0.01,0.0);
      node4->ty+=0.01;
      node4->update_matrices();

    }
    else if (key == GLFW_KEY_KP_6)
      // curr_node->inc_rx();
    {
     cur_cent = cur_cent + glm::vec3(0.0,-0.01,0.0);
      node4->ty-=0.01;
      node4->update_matrices();

    }
    // else if (key == GLFW_KEY_PAGE_UP)
    //   curr_node->dec_rz();
    // else if (key == GLFW_KEY_PAGE_DOWN)
    //   curr_node->inc_rz();
    // else if (key == GLFW_KEY_Y){
    //   node5->ty += 0.2;
    //   node5->update_matrices();
    // }
    else if (key == GLFW_KEY_LEFT_BRACKET){
      if(camera == 1) c1_zpos -= 0.0025;
      else c2_xpos += 0.1;
    }
    else if (key == GLFW_KEY_RIGHT_BRACKET){
      if(camera == 1) c1_zpos += 0.0025;
      c2_xpos -=0.1;
    }
    else if (key == GLFW_KEY_RIGHT){
      if(camera == 1) c1_ypos += 0.0025;
      else c2_ypos += 0.05;
    }
    else if (key == GLFW_KEY_LEFT){
      if(camera == 1) c1_ypos -= 0.0025;
      else c2_ypos -= 0.05;
    }
    else if (key == GLFW_KEY_UP){
      if(camera == 1) c1_xpos += 0.0025;
      else c2_zpos -= 0.05;
    }
    else if (key == GLFW_KEY_DOWN){
      if(camera == 1) c1_xpos -= 0.0025;
      else c2_zpos += 0.05;
    }
    else if (key == GLFW_KEY_KP_0 && action == GLFW_PRESS) // to toggle camera
      camera = 3 - camera;
    else if((key == GLFW_KEY_L && action == GLFW_PRESS) || (key == GLFW_KEY_I && action == GLFW_PRESS)){
      animation = true;
    }
    else if(key == GLFW_KEY_T && action == GLFW_PRESS){
      std::ofstream outfile;
      outfile.open("data/trajectory.txt");

      outfile<<bez_idx<<"\n";
      for(int i=0;i<bez_idx;i++){
        for(int j=0;j<3;j++){
          outfile<<bez_ctrl[i][j]<<" ";
        }
        outfile<<"\n";
      }

      outfile.close();
      std::cout<<"Trajectories saved successfully\n";
    }
    else if(key == GLFW_KEY_Y && action == GLFW_PRESS){
      std::ifstream infile;
      infile.open("data/trajectory.txt");

      infile>>bez_idx;
      for(int i=0;i<bez_idx;i++){
        for(int j=0;j<3;j++){
          infile>>bez_ctrl[i][j];
        }
      }
      sig = 1;

      infile.close();
      std::cout<<"Trajectories loaded successfully\n";
    }
  }
};  
  


