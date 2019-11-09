#include "a3-model-3.hpp"
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
glm::vec2 tex_coords_box[num_vertices];

int prop_idx = 0;
glm::vec4 v_positions_prop[num_vertices];
glm::vec4 v_colors_prop[num_vertices];
glm::vec4 v_normals_prop[num_vertices];
glm::vec2 tex_coords_prop[num_vertices];

int solar_idx = 0;
glm::vec4 v_positions_solar[num_vertices];
glm::vec4 v_colors_solar[num_vertices];
glm::vec4 v_normals_solar[num_vertices];
glm::vec2 tex_coords_solar[num_vertices];

int refl_idx = 0;
glm::vec4 v_positions_refl[num_vertices];
glm::vec4 v_colors_refl[num_vertices];
glm::vec4 v_normals_refl[num_vertices];
glm::vec2 tex_coords_refl[num_vertices];

int extra_idx = 0;
glm::vec4 v_positions_extra[num_vertices];
glm::vec4 v_colors_extra[num_vertices];
glm::vec4 v_normals_extra[num_vertices];
glm::vec2 tex_coords_extra[num_vertices];

glm::vec4 color(1.0, 0.2, 0.2, 1.0);
glm::vec4 silver(0.35, 0.35, 0.35, 1.0);
glm::vec4 black(0.2, 0.2, 0.2, 1.0);
glm::vec4 white(1.0, 1.0, 1.0, 1.0);
glm::vec4 brown(0.67, 0.45, 0.23, 1.0);
glm::vec4 blue(0.0, 0.0, 1.0, 1.0);

glm::vec4 cube[8] = {
    glm::vec4(-1.25, -1.0, 1.0, 1.0),
    glm::vec4(-1.25, 1.0, 1.0, 1.0),
    glm::vec4(1.25, 1.0, 1.0, 1.0),
    glm::vec4(1.25, -1.0, 1.0, 1.0),
    glm::vec4(-1.25, -1.0, -1.0, 1.0),
    glm::vec4(-1.25, 1.0, -1.0, 1.0),
    glm::vec4(1.25, 1.0, -1.0, 1.0),
    glm::vec4(1.25, -1.0, -1.0, 1.0)};

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

void quad(int a, int b, int c, int d)
{
  v_colors_box[box_idx] = brown; v_positions_box[box_idx] = cube[a]; v_normals_box[box_idx] = cube[a]; tex_coords_box[box_idx] = t_coords[1]; box_idx++;
  v_colors_box[box_idx] = brown; v_positions_box[box_idx] = cube[b]; v_normals_box[box_idx] = cube[b]; tex_coords_box[box_idx] = t_coords[0]; box_idx++;
  v_colors_box[box_idx] = brown; v_positions_box[box_idx] = cube[c]; v_normals_box[box_idx] = cube[c]; tex_coords_box[box_idx] = t_coords[2]; box_idx++;
  v_colors_box[box_idx] = brown; v_positions_box[box_idx] = cube[a]; v_normals_box[box_idx] = cube[a]; tex_coords_box[box_idx] = t_coords[1]; box_idx++;
  v_colors_box[box_idx] = brown; v_positions_box[box_idx] = cube[c]; v_normals_box[box_idx] = cube[c]; tex_coords_box[box_idx] = t_coords[2]; box_idx++;
  v_colors_box[box_idx] = brown; v_positions_box[box_idx] = cube[d]; v_normals_box[box_idx] = cube[d]; tex_coords_box[box_idx] = t_coords[3]; box_idx++;
}

void prop(float radius, float sectors, float slices, glm::vec4 v)
{
  float lats, longs, l;

  for (lats = -radius; lats <= 0.0; lats += 0.01)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * cos(longs);
      float z = radius * sin(longs);
      float y = lats;
      glm::vec4 pt(x, y, z, 1.0);

      if (radius >= 0.25)
        v_colors_prop[prop_idx] = silver;
      else
        v_colors_prop[prop_idx] = color;
      v_positions_prop[prop_idx] = pt + v;
      v_normals_prop[prop_idx] = pt;
      tex_coords_prop[prop_idx] = glm::vec2(-lats/radius,longs/(2*PI));
      prop_idx++;

      if (lats > 0.0)
        l = 0.0;
      else
        l = lats + sectors;
      x = radius * cos(longs);
      z = radius * sin(longs);
      y = l;
      pt = glm::vec4(x, y, z, 1.0);
      if (radius >= 0.25)
        v_colors_prop[prop_idx] = silver;
      else
        v_colors_prop[prop_idx] = color;
      v_positions_prop[prop_idx] = pt + v;
      v_normals_prop[prop_idx] = pt;
      tex_coords_prop[prop_idx] = glm::vec2(-lats/radius,longs/(2*PI));
      prop_idx++;
    }
    radius -= 0.005;
  }
}

void propulsor(void){
  float slices = 0.1, sectors = 0.1;
    prop(0.2, sectors, slices, glm::vec4(-0.7, 0.0, -0.7, 0.0));
    prop(0.2, sectors, slices, glm::vec4(-0.7, 0.0, 0.7, 0.0));
    prop(0.2, sectors, slices, glm::vec4(0.7, 0.0, -0.7, 0.0));
    prop(0.2, sectors, slices, glm::vec4(0.7, 0.0, 0.7, 0.0));
    prop(0.5, sectors, slices, glm::vec4(0.0, 0.0, 0.0, 0.0));
}

// generate 12 triangles: 36 vertices and 36 colors
void box(void)
{
  quad(1, 0, 3, 2);
  quad(2, 3, 7, 6);
  quad(3, 0, 4, 7);
  quad(6, 5, 1, 2);
  quad(4, 5, 6, 7);
  quad(5, 4, 0, 1);
}

void extras(void){
  float slices = 0.1, sectors = 0.1;
  float l, lats, longs;
  double radius = 0.55;

  for (lats = 0; lats <= PI; lats += sectors)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_extra[extra_idx] = color;
      v_positions_extra[extra_idx] = pt + glm::vec4(0.0, 1.0, 0.0, 0.0);
      v_normals_extra[extra_idx] = pt;
      tex_coords_extra[extra_idx] = glm::vec2(lats/PI,longs/(2*PI));
      extra_idx++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_extra[extra_idx] = color;
      v_positions_extra[extra_idx] = pt + glm::vec4(0.0, 1.0, 0.0, 0.0);
      v_normals_extra[extra_idx] = pt;
      tex_coords_extra[extra_idx] = glm::vec2(lats/PI,longs/(2*PI));
      extra_idx++;
    }
  }

  radius = 0.15;

  for (lats = 0; lats <= PI / 2; lats += sectors)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float y = radius * sin(lats) * sin(longs);
      float z = radius * cos(lats);
      glm::vec4 pt(x, y + 0.75, z - 1.5, 1.0);

      v_colors_extra[extra_idx] = silver;
      v_positions_extra[extra_idx] = pt;
      v_normals_extra[extra_idx] = pt;
      tex_coords_extra[extra_idx] = glm::vec2(lats/PI,longs/(2*PI));
      extra_idx++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      y = radius * sin(l) * sin(longs);
      z = radius * cos(l);
      pt = glm::vec4(x, y + 0.75, z - 1.5, 1.0);
      v_colors_extra[extra_idx] = silver;
      v_positions_extra[extra_idx] = pt;
      v_normals_extra[extra_idx] = pt;
      tex_coords_extra[extra_idx] = glm::vec2(lats/PI,longs/(2*PI));
      extra_idx++;
    }
  }

  radius = 0.05;

  for (lats = -1; lats >= -1.5; lats -= 0.1)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * cos(longs);
      float y = radius * sin(longs);
      float z = lats;
      glm::vec4 pt(x, y + 0.75, z, 1.0);

      v_colors_extra[extra_idx] = silver;
      v_positions_extra[extra_idx] = pt;
      v_normals_extra[extra_idx] = pt;
      tex_coords_extra[extra_idx] = glm::vec2(lats/PI,longs/(2*PI));
      extra_idx++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * cos(longs);
      y = radius * sin(longs);
      z = l;
      pt = glm::vec4(x, y + 0.75, z, 1.0);
      v_colors_extra[extra_idx] = silver;
      v_positions_extra[extra_idx] = pt;
      v_normals_extra[extra_idx] = pt;
      tex_coords_extra[extra_idx] = glm::vec2(lats/PI,longs/(2*PI));
      extra_idx++;
    }
  }
}

glm::vec4 cuboid[8] = {
    glm::vec4(-0.05, 0.0, 2.0, 1.0),
    glm::vec4(-0.05, 1.75, 2.0, 1.0),
    glm::vec4(0.05, 1.75, 2.0, 1.0),
    glm::vec4(0.05, 0.0, 2.0, 1.0),
    glm::vec4(-0.05, 0.0, 0.0, 1.0),
    glm::vec4(-0.05, 1.75, 0.0, 1.0),
    glm::vec4(0.05, 1.75, 0.0, 1.0),
    glm::vec4(0.05, 0.0, 0.0, 1.0)};

void quad_solar(int a, int b, int c, int d)
{
  glm::vec4 centre(0.0, 1.0, 1.0, 0.0);
  v_colors_solar[solar_idx] = blue; v_positions_solar[solar_idx] = cuboid[a]; v_normals_solar[solar_idx] = cuboid[a] - centre; tex_coords_solar[solar_idx] = t_coords[1]; solar_idx++;
  v_colors_solar[solar_idx] = blue; v_positions_solar[solar_idx] = cuboid[b]; v_normals_solar[solar_idx] = cuboid[b] - centre; tex_coords_solar[solar_idx] = t_coords[0]; solar_idx++;
  v_colors_solar[solar_idx] = blue; v_positions_solar[solar_idx] = cuboid[c]; v_normals_solar[solar_idx] = cuboid[c] - centre; tex_coords_solar[solar_idx] = t_coords[2]; solar_idx++;
  v_colors_solar[solar_idx] = blue; v_positions_solar[solar_idx] = cuboid[a]; v_normals_solar[solar_idx] = cuboid[a] - centre; tex_coords_solar[solar_idx] = t_coords[1]; solar_idx++;
  v_colors_solar[solar_idx] = blue; v_positions_solar[solar_idx] = cuboid[c]; v_normals_solar[solar_idx] = cuboid[c] - centre; tex_coords_solar[solar_idx] = t_coords[2]; solar_idx++;
  v_colors_solar[solar_idx] = blue; v_positions_solar[solar_idx] = cuboid[d]; v_normals_solar[solar_idx] = cuboid[d] - centre; tex_coords_solar[solar_idx] = t_coords[3]; solar_idx++;
}

// generate 12 triangles: 36 vertices and 36 colors
void solar(void)
{
  quad_solar(1, 0, 3, 2);
  quad_solar(2, 3, 7, 6);
  quad_solar(3, 0, 4, 7);
  quad_solar(6, 5, 1, 2);
  quad_solar(4, 5, 6, 7);
  quad_solar(5, 4, 0, 1);
}

void reflector(double radius)
{
  float Lats = 360, Longs = 360;

  float slices = (180 / (float(Lats) * 10)) / 2;
  float sectors = (180 / (float(Longs) * 10)) / 2;

  float l, lats, longs;

  for (lats = PI / 6; lats >= 0; lats -= sectors)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float z = radius * sin(lats) * cos(longs);
      float y = radius * sin(lats) * sin(longs);
      float x = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_refl[refl_idx] = silver;
      v_positions_refl[refl_idx] = pt + glm::vec4(-2.6, 1.5, 0.0, 0.0);
      v_normals_refl[refl_idx] = pt;
      tex_coords_refl[refl_idx] = glm::vec2(6*lats/PI, longs/(2*PI));
      refl_idx++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      z = radius * sin(l) * cos(longs);
      y = radius * sin(l) * sin(longs);
      x = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_refl[refl_idx] = silver;
      v_positions_refl[refl_idx] = pt + glm::vec4(-2.6, 1.5, 0.0, 0.0);
      v_normals_refl[refl_idx] = pt;
      tex_coords_refl[refl_idx] = glm::vec2(6*lats/PI, longs/(2*PI));
      refl_idx++;
    }
  }
}

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("src/payload/07_vshader_tex.glsl");
  std::string fragment_shader_file("src/payload/07_fshader_tex.glsl");

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

  GLuint tex1=LoadTexture("src/payload/images/launchpad1.bmp",2047,2047);
  GLuint tex2=LoadTexture("src/payload/images/launchpad2.bmp",408,236);
  GLuint tex_solar=LoadTexture("src/payload/images/solar2.bmp",390,220);
  GLuint tex_refl = LoadTexture("src/payload/images/refl2.bmp",280,280);
  GLuint tex_prop = LoadTexture("src/payload/images/refl2.bmp",280,280);
  GLuint tex_box = LoadTexture("src/payload/images/box2.bmp",2400,1800);
  GLuint tex_extra = LoadTexture("src/payload/images/extra.bmp",450,422);
  glBindTexture(GL_TEXTURE_2D, tex1);

  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  box();
  solar();
  reflector(3);
  propulsor();
  extras();

  //note that the buffers are initialized in the respective constructors

  node1 = new csX75::HNode(NULL, num_vertices, v_positions_box, v_colors_box, v_normals_box, tex_coords_box, sizeof(v_positions_box), sizeof(v_colors_box), sizeof(v_normals_box), sizeof(tex_coords_box), false, tex_box);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_prop, v_colors_prop, v_normals_prop, tex_coords_prop, sizeof(v_positions_prop), sizeof(v_colors_prop), sizeof(v_normals_prop), sizeof(tex_coords_prop), false, tex_prop);
  node2->change_parameters(0.0, -1.0, 0.0, 0.0, 0.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_extra, v_colors_extra, v_normals_extra, tex_coords_extra, sizeof(v_positions_extra), sizeof(v_colors_extra), sizeof(v_normals_extra), sizeof(tex_coords_extra), false, tex_extra);
  node2->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_solar, v_colors_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_colors_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false, tex_solar);
  node2->change_parameters(-1.35, 0.0, -1.0, 0.0, 0.0, 0.0);
  node3 = new csX75::HNode(node2, num_vertices, v_positions_solar, v_colors_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_colors_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false, tex_solar);
  node3->change_parameters(0.0, 0.0, -0.1, 0.0, 0.0, 0.0);
  node4 = new csX75::HNode(node2, num_vertices, v_positions_solar, v_colors_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_colors_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false, tex_solar);
  node4->change_parameters(0.0, 0.0, 2.1, 0.0, 180.0, 0.0);
  node5 = new csX75::HNode(node1, num_vertices, v_positions_refl, v_colors_refl, v_normals_refl, tex_coords_refl, sizeof(v_positions_refl), sizeof(v_colors_refl), sizeof(v_normals_refl), sizeof(tex_coords_refl), false, tex_refl);
  node5->change_parameters(1.35, -1.0, 0.0, 0.0, 0.0, 0.0);
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
    projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
  //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);

  view_matrix = projection_matrix * lookat_matrix;

  // modelview_matrix = view_matrix * model_matrix;
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // normal_matrix = glm::transpose(glm::inverse(glm::mat3(modelview_matrix)));
  // glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

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
