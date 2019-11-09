#include "a3_model.hpp"
#include "texture.hpp"

int tesselation = 50;
bool wireframe = false;

double PI = 3.14159265;
GLuint shaderProgram,uniformTex0,uniformTex1;
// GLuint vbo[5], vao[5];
// GLuint tex;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;

glm::mat4 modelview_matrix;
glm::mat4 normal_matrix;

GLuint uModelViewMatrix,texCoord,vPosition,vNormal;
GLuint modelMatrix;
GLuint normalMatrix;
//-----------------------------------------------------------------

const int num_vertices = 100000;

int tri_idx = 0;
glm::vec4 v_positions[num_vertices];
// glm::vec4 v_colors[num_vertices];
glm::vec4 v_normals[num_vertices];
glm::vec3 tex_coords[num_vertices];

int trii = 0;
glm::vec4 spv_positions[num_vertices];
// glm::vec4 v_colors[num_vertices];
glm::vec4 spv_normals[num_vertices];
glm::vec3 sptex_coords[num_vertices];

int tric = 0;
glm::vec4 cpv_positions[num_vertices];
// glm::vec4 v_colors[num_vertices];
glm::vec4 cpv_normals[num_vertices];
glm::vec3 cptex_coords[num_vertices];

int trisun = 0;
glm::vec4 sv_positions[num_vertices];
// glm::vec4 v_colors[num_vertices];
glm::vec4 sv_normals[num_vertices];
glm::vec3 stex_coords[num_vertices];

int trimars = 0;
glm::vec4 mrsv_positions[num_vertices];
// glm::vec4 v_colors[num_vertices];
glm::vec4 mrsv_normals[num_vertices];
glm::vec3 mrstex_coords[num_vertices];

double Radius1 = 0.7, Radius2 = 8,Radius3 = 0.7001,Radius4 = 0.2, Radius5 = 0.7;
int Lat = 10;
int Long = 10;

void space(double radius, int Lats, int Longs)
{
  float lats, longs;

  float slices = (2 * PI) / Longs;
  float sectors = (PI) / Lats;
  float l;

  for (lats = 0.0; lats < PI; lats += sectors)
  {
    for (longs = 0.0; longs < 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(-longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);
      glm::vec4 norm(x, y, z, 0.0);

      // v_colors[tri_idx] = white;
      spv_positions[trii] = pt;
      spv_normals[trii] = -norm;

      // Texture coordinates of a point //
      GLfloat u = longs / (2 * PI), v = 1 - lats / PI;
      sptex_coords[trii] = glm::vec3(u, v,0);
      trii++;
      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(-longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      norm = glm::vec4(x, y, z, 0.0);
      // v_colors[tri_idx] = white;
      spv_positions[trii] = pt;
      spv_normals[trii] = -norm;
      u = longs / (2 * PI);
      v = 1 - l / PI;
      // // std::cout<<u<<" "<<v<<"\n";
      sptex_coords[trii] = glm::vec3(u, v,0);
      trii++;
    }
  }
}

void earth(double radius, int Lats, int Longs)
{
  float lats, longs;

  float slices = (2 * PI) / Longs;
  float sectors = (PI) / Lats;
  float l;

  for (lats = 0.0; lats < PI; lats += sectors)
  {
    for (longs = 0.0; longs < 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(-longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);
      glm::vec4 norm(x, y, z, 0.0);

      // v_colors[tri_idx] = white;
      v_positions[tri_idx] = pt;
      v_normals[tri_idx] = norm;

      // Texture coordinates of a point //
      GLfloat u = longs / (2 * PI), v = 1 - lats / PI;
      tex_coords[tri_idx] = glm::vec3(u, v,0);
      tri_idx++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(-longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      norm = glm::vec4(x, y, z, 0.0);
      // v_colors[tri_idx] = white;
      v_positions[tri_idx] = pt;
      v_normals[tri_idx] = norm;
      u = longs / (2 * PI);
      v = 1 - l / PI;
      // // std::cout<<u<<" "<<v<<"\n";
      tex_coords[tri_idx] = glm::vec3(u, v,0);
      tri_idx++;
    }
  }
}
void mars(double radius, int Lats, int Longs)
{
  float lats, longs;

  float slices = (2 * PI) / Longs;
  float sectors = (PI) / Lats;
  float l;

  for (lats = 0.0; lats < PI; lats += sectors)
  {
    for (longs = 0.0; longs < 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(-longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);
      glm::vec4 norm(x, y, z, 0.0);

      // v_colors[tri_idx] = white;
      mrsv_positions[trimars] = pt;
      mrsv_normals[trimars] = norm;

      // Texture coordinates of a point //
      GLfloat u = longs / (2 * PI), v = 1 - lats / PI;
      mrstex_coords[trimars] = glm::vec3(u, v,2);
      trimars++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(-longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      norm = glm::vec4(x, y, z, 0.0);
      // v_colors[tri_idx] = white;
      mrsv_positions[trimars] = pt;
      mrsv_normals[trimars] = norm;
      u = longs / (2 * PI);
      v = 1 - l / PI;
      // // std::cout<<u<<" "<<v<<"\n";
      mrstex_coords[trimars] = glm::vec3(u, v,2);
      trimars++;
    }
  }
}



void sun(double radius, int Lats, int Longs)
{
  float lats, longs;

  float slices = (2 * PI) / Longs;
  float sectors = (PI) / Lats;
  float l;

  for (lats = 0.0; lats < PI; lats += sectors)
  {
    for (longs = 0.0; longs < 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(-longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);
      glm::vec4 norm(x, y, z, 0.0);

      // v_colors[tri_idx] = white;
      sv_positions[trisun] = pt;
      sv_normals[trisun] = -norm;

      // Texture coordinates of a point //
      GLfloat u = longs / (2 * PI), v = 1 - lats / PI;
      stex_coords[trisun] = glm::vec3(u, v,0);
      trisun++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(-longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      norm = glm::vec4(x, y, z, 0.0);
      // v_colors[tri_idx] = white;
      sv_positions[trisun] = pt;
      sv_normals[trisun] = -norm;
      u = longs / (2 * PI);
      v = 1 - l / PI;
      // // std::cout<<u<<" "<<v<<"\n";
      stex_coords[trisun] = glm::vec3(u, v,0);
      trisun++;
    }
  }
}


void clouds(double radius, int Lats, int Longs)
{
  float lats, longs;

  float slices = (2 * PI) / Longs;
  float sectors = (PI) / Lats;
  float l;

  for (lats = 0.0; lats < PI; lats += sectors)
  {
    for (longs = 0.0; longs < 2.0 * PI; longs += slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(-longs);
      float y = radius * cos(lats);
      glm::vec4 pt(x, y, z, 1.0);
      glm::vec4 norm(x, y, z, 0.0);

      // v_colors[tri_idx] = white;
      cpv_positions[tric] = pt;
      cpv_normals[tric] = norm;

      // Texture coordinates of a point //
      GLfloat u = longs / (2 * PI), v = 1 - lats / PI;
      cptex_coords[tric] = glm::vec3(u, v,1);
      tric++;

      if (lats + sectors > PI)
        l = PI;
      else
        l = lats + sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(-longs);
      y = radius * cos(l);
      pt = glm::vec4(x, y, z, 1.0);
      norm = glm::vec4(x, y, z, 0.0);
      // v_colors[tri_idx] = white;
      cpv_positions[tric] = pt;
      cpv_normals[tric] = norm;
      u = longs / (2 * PI);
      v = 1 - l / PI;
      // // std::cout<<u<<" "<<v<<"\n";
      cptex_coords[tric] = glm::vec3(u, v,1);
      tric++;
    }
  }
}





void load_earth(){
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





//-----------------------------------------------------------------

GLuint texd,texn,texc, tex2,texsun,texmars;

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("a3_vshader.glsl");
  std::string fragment_shader_file("a3_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram(shaderProgram);

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation(shaderProgram, "vPosition");
  // GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
  vNormal = glGetAttribLocation(shaderProgram, "vNormal");
  texCoord = glGetAttribLocation(shaderProgram, "texCoord");
  uModelViewMatrix = glGetUniformLocation(shaderProgram, "uModelViewMatrix");
  normalMatrix = glGetUniformLocation(shaderProgram, "normalMatrix");
  modelMatrix = glGetUniformLocation(shaderProgram, "modelMatrix");
  uniformTex0 = glGetUniformLocation( shaderProgram, "texturun" );
  uniformTex1 = glGetUniformLocation( shaderProgram, "tex1" );
  // Load Textures
  // glBindTexture(GL_TEXTURE_2D, tex);
  // glBindTexture(GL_TEXTURE_2D, tex);
  texd = LoadTexture("images/2k_earth_daymap.bmp", 2048, 1024);
  texn = LoadTexture("images/2k_earth_nightmap.bmp", 2048, 1024);
  texc = LoadTexture("images/2k_earth_clouds.bmp", 2048, 1024);
  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, tex2);
  tex2 = LoadTexture("images/2k_stars_milky_way.bmp", 2048, 1024);
  texsun = LoadTexture("images/2k_sun.bmp", 2048, 1024);
  texmars = LoadTexture("images/2k_mars.bmp", 2048, 1024);
  // glBindTexture(GL_TEXTURE_2D, tex);
  // glActiveTexture(GL_TEXTURE1);
  //Ask GL for two Vertex Attribute Objects (vao) , one for the colorcube and one for the plane.
  
  /*******************
  // glGenVertexArrays(5, vao);
  // //Ask GL for two Vertex Buffer Object (vbo)
  // glGenBuffers(5, vbo);
  ***********************/
  //Set 0 as the current array to be used by binding it

  // Call the sphere function
  Lat = 200;
  Long = 200;
  load_earth();
  // earth(Radius1, Lat, Long);
  // space(Radius2, Lat, Long);
  // clouds(Radius3,Lat,Long);
  // sun(Radius4,Lat,Long);
  // mars(Radius5,Lat,Long);
  

  node1 = new csX75::HNode(NULL,num_vertices,texsun,texsun,sv_positions,stex_coords,sv_normals,sizeof(sv_positions),sizeof(stex_coords),sizeof(sv_normals));
  node1->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  node2 = new csX75::HNode(node1,num_vertices,texd,texn,v_positions,tex_coords,v_normals,sizeof(v_positions),sizeof(tex_coords),sizeof(v_normals));
  node2->change_parameters(0.0,-3.0,0.0,0.0,0.0,0.0);
  node3 = new csX75::HNode(node1,num_vertices,texmars,texmars,mrsv_positions,mrstex_coords,mrsv_normals,sizeof(mrsv_positions),sizeof(mrstex_coords),sizeof(mrsv_normals));
  node3->change_parameters(0.0,-5.5,0.0,10.0,90.0,10.0);
  node4 = new csX75::HNode(node1,num_vertices,tex2,tex2,spv_positions,sptex_coords,spv_normals,sizeof(spv_positions),sizeof(sptex_coords),sizeof(spv_normals));
  node5 = new csX75::HNode(node2,num_vertices,texc,texc,cpv_positions,cptex_coords,cpv_normals,sizeof(cpv_positions),sizeof(cptex_coords),sizeof(cpv_normals));  
  // node5->change_parameters(1.0,1.0,1.0,0.0,0.0,0.0);
  root_node = curr_node = node5;

}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  matrixStack.clear();

  /*
  rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f, 0.0f, 0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f, 1.0f, 0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f, 0.0f, 1.0f));
  model_matrix = rotation_matrix;
  */

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f, 0.0f, 0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f, 1.0f, 0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f, 0.0f, 1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos, c_ypos, c_zpos, 1.0) * c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x, c_up_y, c_up_z, 1.0) * c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos), glm::vec3(0.0), glm::vec3(c_up));

  //creating the projection matrix

    projection_matrix = glm::frustum(-0.01, 0.01, -0.01, 0.01, 0.01, 15.0);
  // projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 5.0);

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
  if (argc > 1)
    tesselation = atoi(argv[1]);
  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475 Assignment 3: Texture Mapping", NULL, NULL);
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
