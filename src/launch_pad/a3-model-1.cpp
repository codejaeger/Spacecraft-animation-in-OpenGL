#include "a3-model-1.hpp"
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

int box_idx = 0;
glm::vec4 v_positions_box[num_vertices];
glm::vec4 v_colors_box[num_vertices];
glm::vec4 v_normals_box[num_vertices];

int plat_idx = 0;
glm::vec4 v_positions_plat[num_vertices];
glm::vec4 v_colors_plat[num_vertices];
glm::vec4 v_normals_plat[num_vertices];

int w1_idx = 0;
glm::vec4 v_positions_w1[num_vertices];
glm::vec4 v_colors_w1[num_vertices];
glm::vec4 v_normals_w1[num_vertices];
glm::vec2 tex_coords_w1[num_vertices];

int w2_idx = 0;
glm::vec4 v_positions_w2[num_vertices];
glm::vec4 v_colors_w2[num_vertices];
glm::vec4 v_normals_w2[num_vertices];

int w3_idx = 0;
glm::vec4 v_positions_w3[num_vertices];
glm::vec4 v_colors_w3[num_vertices];
glm::vec4 v_normals_w3[num_vertices];

glm::vec4 color(1.0, 0.2, 0.2, 1.0);
glm::vec4 silver(0.35, 0.35, 0.35, 1.0);
glm::vec4 black(0.2, 0.2, 0.2, 1.0);
glm::vec4 white(1.0, 1.0, 1.0, 1.0);
glm::vec4 brown(0.67, 0.45, 0.23, 1.0);
glm::vec4 blue(0.0, 0.0, 1.0, 1.0);

glm::vec4 cube[8] = {
    glm::vec4(-1.5, -0.25, 1.0, 1.0),
    glm::vec4(-1.5, 0.25, 1.0, 1.0),
    glm::vec4(1.5, 0.25, 1.0, 1.0),
    glm::vec4(1.5, -0.25, 1.0, 1.0),
    glm::vec4(-1.5, -0.25, -1.0, 1.0),
    glm::vec4(-1.5, 0.25, -1.0, 1.0),
    glm::vec4(1.5, 0.25, -1.0, 1.0),
    glm::vec4(1.5, -0.25, -1.0, 1.0)};

void quad(int a, int b, int c, int d)
{ 
  v_colors_plat[plat_idx] = silver; v_positions_plat[plat_idx] = cube[a]; v_normals_plat[plat_idx] = cube[a]; plat_idx++;
  v_colors_plat[plat_idx] = silver; v_positions_plat[plat_idx] = cube[b]; v_normals_plat[plat_idx] = cube[b]; plat_idx++;
  v_colors_plat[plat_idx] = silver; v_positions_plat[plat_idx] = cube[c]; v_normals_plat[plat_idx] = cube[c]; plat_idx++;
  v_colors_plat[plat_idx] = silver; v_positions_plat[plat_idx] = cube[a]; v_normals_plat[plat_idx] = cube[a]; plat_idx++;
  v_colors_plat[plat_idx] = silver; v_positions_plat[plat_idx] = cube[c]; v_normals_plat[plat_idx] = cube[c]; plat_idx++;
  v_colors_plat[plat_idx] = silver; v_positions_plat[plat_idx] = cube[d]; v_normals_plat[plat_idx] = cube[d]; plat_idx++;
}

void platform(void)
{
  plat_idx = 0;
  quad(1, 0, 3, 2);
  quad(2, 3, 7, 6);
  quad(3, 0, 4, 7);
  quad(6, 5, 1, 2);
  quad(4, 5, 6, 7);
  quad(5, 4, 0, 1);
}
// generate 12 triangles: 36 vertices and 36 colors
void box(void)
{
  float slices = 0.1, sectors = 0.1;
  float l, lats, longs;
  double radius = 0.7;

  for (lats = 0; lats <= 4.0; lats += 0.4)
  {
    for (longs = PI/4; longs <= 2.0 * PI; longs += PI/2)
    {
      // std::cout<<lats<<" ";
      float x = radius * cos(longs);
      float z = radius * sin(longs);
      float y = lats;
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_box[box_idx] = color;
      v_positions_box[box_idx] = pt+glm::vec4(0.8,0.0,0.0,0.0);
      v_normals_box[box_idx] = pt;
      box_idx++;

      if (lats + 0.4 > 4.0)
        l = 4.0;
      else
        l = lats + 0.4;
      // std::cout<<l<<" ";
      x = radius * cos(longs);
      z = radius * sin(longs);
      y = l;
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_box[box_idx] = color;
      v_positions_box[box_idx] = pt+glm::vec4(0.8,0.0,0.0,0.0);
      v_normals_box[box_idx] = pt;
      box_idx++;
    }
  }

  for (lats = 4.0; lats >= 0.0; lats -= 0.4)
  {
    for (longs = PI/4; longs <= 2.0 * PI; longs += PI/2)
    {
      // std::cout<<lats<<" ";
      float x = radius * cos(longs);
      float z = radius * sin(longs);
      float y = lats;
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_box[box_idx] = color;
      v_positions_box[box_idx] = pt+glm::vec4(0.8,0.0,0.0,0.0);
      v_normals_box[box_idx] = pt;
      box_idx++;

      if (lats - 0.4 < 0.0)
        l = 0.0;
      else
        l = lats - 0.4;
      // std::cout<<l<<" ";
      x = radius * cos(longs);
      z = radius * sin(longs);
      y = l;
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_box[box_idx] = color;
      v_positions_box[box_idx] = pt+glm::vec4(0.8,0.0,0.0,0.0);
      v_normals_box[box_idx] = pt;
      box_idx++;
    }
  }

  for (lats = 0.0; lats <= 4.0; lats += 0.4)
  {
    for (longs = PI/4; longs <= 2.0 * PI; longs += PI/2)
    {
      float x = radius * cos(longs);
      float z = radius * sin(longs);
      float y = lats;
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_box[box_idx] = color;
      v_positions_box[box_idx] = pt+glm::vec4(0.8,0.0,0.0,0.0);
      v_normals_box[box_idx] = pt;
      box_idx++;
    }
  }
}

glm::vec4 cube1[8] = {
    glm::vec4(-0.25, 0.0, 1.0, 1.0),
    glm::vec4(-0.25, 6.0, 1.0, 1.0),
    glm::vec4(0.25, 6.0, 1.0, 1.0),
    glm::vec4(0.25, 0.0, 1.0, 1.0),
    glm::vec4(-0.25, 0.0, -1.0, 1.0),
    glm::vec4(-0.25, 6.0, -1.0, 1.0),
    glm::vec4(0.25, 6.0, -1.0, 1.0),
    glm::vec4(0.25, 0.0, -1.0, 1.0)};

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

void quad1(int a, int b, int c, int d)
{ 
  glm::vec4 centre(0.0,3.0,0.0,0.0);
  v_colors_w1[w1_idx] = brown; v_positions_w1[w1_idx] = cube1[a]; v_normals_w1[w1_idx] = cube1[a] - centre; tex_coords_w1[w1_idx] = t_coords[1]; w1_idx++;
  v_colors_w1[w1_idx] = brown; v_positions_w1[w1_idx] = cube1[b]; v_normals_w1[w1_idx] = cube1[b] - centre; tex_coords_w1[w1_idx] = t_coords[0]; w1_idx++;
  v_colors_w1[w1_idx] = brown; v_positions_w1[w1_idx] = cube1[c]; v_normals_w1[w1_idx] = cube1[c] - centre; tex_coords_w1[w1_idx] = t_coords[2]; w1_idx++;
  v_colors_w1[w1_idx] = brown; v_positions_w1[w1_idx] = cube1[a]; v_normals_w1[w1_idx] = cube1[a] - centre; tex_coords_w1[w1_idx] = t_coords[1]; w1_idx++;
  v_colors_w1[w1_idx] = brown; v_positions_w1[w1_idx] = cube1[c]; v_normals_w1[w1_idx] = cube1[c] - centre; tex_coords_w1[w1_idx] = t_coords[2]; w1_idx++;
  v_colors_w1[w1_idx] = brown; v_positions_w1[w1_idx] = cube1[d]; v_normals_w1[w1_idx] = cube1[d] - centre; tex_coords_w1[w1_idx] = t_coords[3]; w1_idx++;
}

void wall1(void)
{
  w1_idx = 0;
  quad1(1, 0, 3, 2);
  quad1(2, 3, 7, 6);
  quad1(3, 0, 4, 7);
  quad1(6, 5, 1, 2);
  quad1(4, 5, 6, 7);
  quad1(5, 4, 0, 1);
}

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("src/launch_pad/07_vshader_tex.glsl");
  std::string fragment_shader_file("src/launch_pad/07_fshader_tex.glsl");

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

  GLuint tex1=LoadTexture("src/launch_pad/images/launchpad1.bmp",2047,2047);
  GLuint tex2=LoadTexture("src/launch_pad/images/launchpad2.bmp",408,236);
  // tex=LoadTexture("images/all1.bmp",256,256);
  // glBindTexture(GL_TEXTURE_2D, tex);

  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  box();
  platform();
  wall1();

  //note that the buffers are initialized in the respective constructors
  node1 = new csX75::HNode(NULL, num_vertices, v_positions_w1, v_colors_w1, v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_colors_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false, tex2);
  node1->change_parameters(2.0, -3.0, 0.0, 0.0, 0.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_w1, v_colors_w1, v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_colors_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false, tex2);
  node2->change_parameters(-0.75, 0.0, -1.25, 0.0, 90.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_w1, v_colors_w1, v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_colors_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false, tex2);
  node2->change_parameters(-0.75, 0.0, 1.25, 0.0, 90.0, 0.0);
  node3 = new csX75::HNode(node1, num_vertices, v_positions_plat, v_colors_plat, v_normals_plat, tex_coords_w1, sizeof(v_positions_plat), sizeof(v_colors_plat), sizeof(v_normals_plat), sizeof(tex_coords_w1), false, tex1);
  node3->change_parameters(-1.75, 0.25, 0.0, 0.0, 0.0, 0.0);
  node4 = new csX75::HNode(node3, num_vertices, v_positions_box, v_colors_box, v_normals_box, tex_coords_w1, sizeof(v_positions_box), sizeof(v_colors_box), sizeof(v_normals_box), sizeof(tex_coords_w1), true, tex1);
  node4->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
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
    projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 20.0);
  //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 20.0);

  view_matrix = projection_matrix * lookat_matrix;

  matrixStack.push_back(view_matrix);

  node1->render_tree();
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
