#include "a3-model-0.hpp"
#include "texture.cpp"

double PI = 3.14159265;
GLuint shaderProgram;
GLuint vbo_box[2], vao_box[2];
GLuint vbo_solar[2], vao_solar[2];
GLuint vbo_refl[2], vao_refl[2];
GLuint tex;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;
glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;

GLuint uModelViewMatrix;
GLuint viewMatrix;
GLuint normalMatrix;
GLuint texCoord;

//-----------------------------------------------------------------

const int num_vertices = 100000;

int earth_idx = 0;
glm::vec4 v_positions_earth[num_vertices];
glm::vec4 v_colors_earth[num_vertices];
glm::vec4 v_normals_earth[num_vertices];
glm::vec2 tex_coords_earth[num_vertices];

int space_idx = 0;
glm::vec4 v_positions_space[num_vertices];
glm::vec4 v_colors_space[num_vertices];
glm::vec4 v_normals_space[num_vertices];
glm::vec2 tex_coords_space[num_vertices];

int cloud_idx = 0;
glm::vec4 v_positions_cloud[num_vertices];
glm::vec4 v_colors_cloud[num_vertices];
glm::vec4 v_normals_cloud[num_vertices];
glm::vec2 tex_coords_cloud[num_vertices];

glm::vec4 color(1.0, 0.2, 0.2, 1.0);
glm::vec4 silver(0.35, 0.35, 0.35, 1.0);
glm::vec4 black(0.2, 0.2, 0.2, 1.0);
glm::vec4 white(1.0, 1.0, 1.0, 1.0);
glm::vec4 brown(0.67, 0.45, 0.23, 1.0);
glm::vec4 blue(0.0, 0.0, 1.0, 1.0);

void earth(double radius, int Lats, int Longs)
{
  float lats, longs;

  float slices = (2 * PI) / Longs;
  float sectors = (PI) / Lats;
  float l;

  for (lats = 0.0; lats <= PI; lats += sectors)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(-longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);

      // v_colors[tri_idx] = white;
      v_positions_earth[earth_idx] = pt;
      v_normals_earth[earth_idx] = pt;
      tex_coords_earth[earth_idx] = glm::vec2(longs/(2*PI),1-lats/PI);
      earth_idx++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(-longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      // v_colors[earth_idx] = white;
      v_positions_earth[earth_idx] = pt;
      v_normals_earth[earth_idx] = pt;
      // // std::cout<<u<<" "<<v<<"\n";
      tex_coords_earth[earth_idx] = glm::vec2(longs/(2*PI),1-l/PI);
      earth_idx++;
    }
  }
}

void space(double radius, int Lats, int Longs)
{
  float lats, longs;

  float slices = (2 * PI) / Longs;
  float sectors = (PI) / Lats;
  float l;

  for (lats = 0.0; lats <= PI; lats += sectors)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(-longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);

      // v_colors[tri_idx] = white;
      v_positions_space[space_idx] = pt;
      v_normals_space[space_idx] = -pt;
      tex_coords_space[space_idx] = glm::vec2(longs/(2*PI),1-lats/PI);
      space_idx++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(-longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      // v_colors[space_idx] = white;
      v_positions_space[space_idx] = pt;
      v_normals_space[space_idx] = -pt;
      // // std::cout<<u<<" "<<v<<"\n";
      tex_coords_space[space_idx] = glm::vec2(longs/(2*PI),1-l/PI);
      space_idx++;
    }
  }
}

void clouds(double radius, int Lats, int Longs)
{
  float lats, longs;

  float slices = (2 * PI) / Longs;
  float sectors = (PI) / Lats;
  float l;

  for (lats = 0.0; lats <= PI; lats += sectors)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(-longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);

      // v_colors[tri_idx] = white;
      v_positions_cloud[cloud_idx] = pt;
      v_normals_cloud[cloud_idx] = pt;
      tex_coords_cloud[cloud_idx] = glm::vec2(longs/(2*PI),1-lats/PI);
      cloud_idx++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(-longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      // v_colors[cloud_idx] = white;
      v_positions_cloud[cloud_idx] = pt;
      v_normals_cloud[cloud_idx] = pt;
      // // std::cout<<u<<" "<<v<<"\n";
      tex_coords_cloud[cloud_idx] = glm::vec2(longs/(2*PI),1-l/PI);
      cloud_idx++;
    }
  }
}

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("src/earth/07_vshader_tex.glsl");
  std::string fragment_shader_file("src/earth/07_fshader_tex.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram(shaderProgram);

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation(shaderProgram, "vPosition");
  vColor = glGetAttribLocation(shaderProgram, "vColor");
  vNormal = glGetAttribLocation(shaderProgram, "vNormal");
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
  uModelViewMatrix = glGetUniformLocation(shaderProgram, "uModelViewMatrix");
  normalMatrix = glGetUniformLocation(shaderProgram, "normalMatrix");
  viewMatrix = glGetUniformLocation(shaderProgram, "viewMatrix");

  GLuint tex_earth = LoadTexture("src/earth/images/2k_earth_daymap.bmp", 2048, 1024);
  GLuint tex_space = LoadTexture("src/earth/images/space1.bmp", 800, 800);
  GLuint tex_cloud = LoadTexture("src/earth/images/2k_earth_clouds.bmp", 2048, 1024);

  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  earth(1, 180, 180);
  space(5,180,180);
  // clouds(2,180,180);

  //note that the buffers are initialized in the respective constructors

  node1 = new csX75::HNode(NULL, num_vertices, v_positions_earth, v_colors_earth, v_normals_earth, tex_coords_earth, sizeof(v_positions_earth), sizeof(v_colors_earth), sizeof(v_normals_earth), sizeof(tex_coords_earth), false, tex_earth);
  node2 = new csX75::HNode(NULL, num_vertices, v_positions_space, v_colors_space, v_normals_space, tex_coords_space, sizeof(v_positions_space), sizeof(v_colors_space), sizeof(v_normals_space), sizeof(tex_coords_space), false, tex_space);
  node3 = new csX75::HNode(NULL, num_vertices, v_positions_cloud, v_colors_cloud, v_normals_cloud, tex_coords_cloud, sizeof(v_positions_cloud), sizeof(v_colors_cloud), sizeof(v_normals_cloud), sizeof(tex_coords_cloud), false, tex_cloud);
  // node2->change_parameters(0.0, 0.0, 0.0, 0.0, 180, 0.0);
  root_node = curr_node = node1;
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f, 0.0f, 0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f, 1.0f, 0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f, 0.0f, 1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos, c_ypos, c_zpos, 1.0) * c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x, c_up_y, c_up_z, 1.0) * c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos), glm::vec3(0.0), glm::vec3(c_up));

  //creating the projection matrix
  if (enable_perspective)
    projection_matrix = glm::frustum(-0.1, 0.1, -0.1, 0.1, 0.1, 10.0);
  //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-1.5, 1.5, -1.5, 1.5, -5.0, 5.0);

  view_matrix = projection_matrix * lookat_matrix;

  // modelview_matrix = view_matrix * model_matrix;
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // normal_matrix = glm::transpose(glm::inverse(glm::mat3(modelview_matrix)));
  // glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

  matrixStack.push_back(view_matrix);

  node1->render_tree();
  node2->render_tree();
  node3->render_tree();
}

int main(int argc, char **argv)
{
  //! The pointer to the GLFW window
  GLFWwindow *window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  //! Make the window's context current
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    //Problem: glewInit failed, something is seriously wrong.
    std::cerr << "GLEW Init Failed : %s" << std::endl;
  }

  //Print and see what context got enabled
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
  {

    // Render here
    renderGL();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------
