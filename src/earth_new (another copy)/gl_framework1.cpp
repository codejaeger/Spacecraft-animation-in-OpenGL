#include "gl_framework.hpp"

extern GLfloat xrot,yrot,zrot,c_xrot,c_yrot,c_zrot,c_xpos,c_ypos,c_zpos;
extern int tesselation;
extern bool enable_perspective,wireframe;

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
//     else if (key == GLFW_KEY_P && action == GLFW_PRESS)
//       enable_perspective = !enable_perspective;   
//     else if (key == GLFW_KEY_A  && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
//       yrot += 1.0;
//     else if (key == GLFW_KEY_A  && action == GLFW_PRESS)
//       yrot -= 1.0;
//     else if (key == GLFW_KEY_D  && action == GLFW_PRESS && mods==GLFW_MOD_SHIFT)
//       xrot += 1.0;
//     else if (key == GLFW_KEY_D  && action == GLFW_PRESS)
//       xrot -= 1.0;
//     else if (key == GLFW_KEY_RIGHT  && action == GLFW_PRESS)
//       c_xpos += 0.2;
//     else if (key == GLFW_KEY_LEFT  && action == GLFW_PRESS)
//       c_xpos -= 0.2;
//     else if (key == GLFW_KEY_UP  && action == GLFW_PRESS)
//       c_ypos += 0.2;
//     else if (key == GLFW_KEY_DOWN  && action == GLFW_PRESS)// && mods==GLFW_MOD_SHIFT
//       c_ypos -= 0.2;
//     else if (key == GLFW_KEY_RIGHT_BRACKET  && action == GLFW_PRESS)
//       c_zpos += 0.1;
//     else if (key == GLFW_KEY_LEFT_BRACKET  && action == GLFW_PRESS)
//       c_zpos -= 0.1;
//     else if (key == GLFW_KEY_K  && action == GLFW_PRESS){
//       std::ofstream outfile;
//       outfile.open("../../data/a3-model-0.raw");

//       outfile<<earth_idx<<"\n";
//       for(int i=0;i<earth_idx;i++){ // in lexicographic order
//           for(int j=0;j<4;j++){
//             outfile<<v_positions_earth[i][j];
//             outfile<<" ";
//           }
//           for(int j=0;j<4;j++){
//             outfile<<v_colors_earth[i][j]; // color
//             outfile<<" ";
//           }
//           for(int j=0;j<4;j++){
//             outfile<<v_normals_earth[i][j]; // color
//             outfile<<" ";
//           }
//           for(int j=0;j<2;j++){
//             outfile<<tex_coords_earth[i][j]; // color
//             outfile<<" ";
//           }
//           outfile<<"\n";
//       }

//       outfile<<space_idx<<"\n";
//       for(int i=0;i<space_idx;i++){
//           for(int j=0;j<4;j++){
//             outfile<<v_positions_space[i][j];
//             outfile<<" ";
//           }
//           for(int j=0;j<4;j++){
//             outfile<<v_colors_space[i][j]; // color
//             outfile<<" ";
//           }
//           for(int j=0;j<4;j++){
//             outfile<<v_normals_space[i][j]; // color
//             outfile<<" ";
//           }
//           for(int j=0;j<2;j++){
//             outfile<<tex_coords_space[i][j]; // color
//             outfile<<" ";
//           }
//           outfile<<"\n";
//         // }
//       }

//       outfile.close();
//       std::cout<<"Model saved successfully\n";
//     }
//   }
// };  
  



    else if (key == GLFW_KEY_LEFT )
      yrot -= 1.0;
    else if (key == GLFW_KEY_RIGHT )
      yrot += 1.0;
    else if (key == GLFW_KEY_UP )
      xrot -= 1.0;
    else if (key == GLFW_KEY_DOWN )
      xrot += 1.0;
    else if (key == GLFW_KEY_PAGE_UP )
      zrot -= 1.0;
    else if (key == GLFW_KEY_PAGE_DOWN)
      zrot += 1.0;
    else if (key == GLFW_KEY_T && action == GLFW_PRESS)
      {
	if(tesselation < 35)
	  tesselation += 5;
      }
    else if (key == GLFW_KEY_Y && action == GLFW_PRESS)
      {
	if(tesselation > 15)
	  tesselation -= 5;
      }
    else if(key == GLFW_KEY_P && action == GLFW_PRESS)
      wireframe=!wireframe;
    else if (key == GLFW_KEY_A  )
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D  )
      c_xrot += 1.0;
    else if (key == GLFW_KEY_LEFT_BRACKET)
    {
      double del = sqrt(c_xpos*c_xpos+c_ypos*c_ypos+c_zpos*c_zpos);
      double mag= 0.01;
      c_xpos = c_xpos - c_xpos/del * sqrt(mag);
      c_zpos = c_zpos - c_zpos/del * sqrt(mag);
      c_ypos = c_ypos - c_ypos/del * sqrt(mag);
    }
    else if (key == GLFW_KEY_RIGHT_BRACKET)
    {
      double del = sqrt(c_xpos*c_xpos+c_ypos*c_ypos+c_zpos*c_zpos);
      double mag= 0.01;
      c_xpos = c_xpos + c_xpos/del * sqrt(0.00001);
      c_zpos = c_zpos + c_zpos/del * sqrt(0.00001);
      c_ypos = c_ypos + c_ypos/del * sqrt(0.00001);
    }
    // else if (key == GLFW_KEY_RIGHT_BRACKET)
    // {

    // }
    // else if (key == GLFW_KEY_W  )
    //   c_xrot -= 1.0;
    // else if (key == GLFW_KEY_S  )
    //   c_xrot += 1.0;        
    // else if (key == GLFW_KEY_Q  )
    //   c_zrot -= 1.0;
    // else if (key == GLFW_KEY_E  )
    //   c_zrot += 1.0;
    // else if (key == GLFW_KEY_E  )
    //   c_xpos += 1.0;   
  }
};  
  


