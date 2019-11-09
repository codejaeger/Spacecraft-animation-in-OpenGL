#include "a3-model-2.hpp"
#include "texture.cpp"

int tesselation = 50;

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

int cyl1_idx = 0;
glm::vec4 v_positions_cyl1[num_vertices];
glm::vec4 v_colors_cyl1[num_vertices];
glm::vec4 v_normals_cyl1[num_vertices];
glm::vec2 tex_coords_cyl1[num_vertices];

int con1_idx = 0;
glm::vec4 v_positions_con1[num_vertices];
glm::vec4 v_colors_con1[num_vertices];
glm::vec4 v_normals_con1[num_vertices];
glm::vec2 tex_coords_con1[num_vertices];

int cyl2_idx = 0;
glm::vec4 v_positions_cyl2[num_vertices];
glm::vec4 v_colors_cyl2[num_vertices];
glm::vec4 v_normals_cyl2[num_vertices];
glm::vec2 tex_coords_cyl2[num_vertices];

int cyl3_idx = 0;
glm::vec4 v_positions_cyl3[num_vertices];
glm::vec4 v_colors_cyl3[num_vertices];
glm::vec4 v_normals_cyl3[num_vertices];
glm::vec2 tex_coords_cyl3[num_vertices];

int prop_idx = 0;
const int num_vertices2 = 200000;
glm::vec4 v_positions_prop[num_vertices2];
glm::vec4 v_colors_prop[num_vertices2];
glm::vec4 v_normals_prop[num_vertices2];
glm::vec2 tex_coords_prop[num_vertices2];

glm::vec4 color(1.0, 0.2, 0.2, 1.0);
glm::vec4 silver(0.35, 0.35, 0.35, 1.0);
glm::vec4 black(0.2, 0.2, 0.2, 1.0);
glm::vec4 white(1.0, 1.0, 1.0, 1.0);
glm::vec4 brown(0.67, 0.45, 0.23, 1.0);
glm::vec4 blue(0.0, 0.0, 1.0, 1.0);

double Radius = 0.5;
int Lat = 10;
int Long = 10;

void cyl1(double radius, int Lats, int height)
{
  height = 1.2;

  float lats, longs;

  float slices = (180 / (float(Lats) * 10)) / 2;

  float l;

  for (lats = 0.2; lats <= 1.2; lats += 0.01)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * cos(longs);
      float y = lats;
      float z = radius * sin(longs);
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_cyl1[cyl1_idx] = white;
      v_positions_cyl1[cyl1_idx] = pt;
      v_normals_cyl1[cyl1_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl1[cyl1_idx] = glm::vec2(longs/(2*PI),lats/height);
      cyl1_idx++;

      if (lats + 0.1 > 1.2)
        l = 1.2;
      else
        l = lats + 0.1;
      x = radius * cos(longs);
      y = l;
      z = radius * sin(longs);
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_cyl1[cyl1_idx] = white;
      v_positions_cyl1[cyl1_idx] = pt;
      v_normals_cyl1[cyl1_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl1[cyl1_idx] = glm::vec2(longs/(2*PI),l/height);
      cyl1_idx++;
    }
  }

  for (lats = 0.0; lats <= 0.2; lats += 0.01)
  {
    double r = 0.5 +(lats-0.2)*0.5;
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = r * cos(longs);
      float y = lats;
      float z = r * sin(longs);
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_cyl1[cyl1_idx] = color;
      v_positions_cyl1[cyl1_idx] = pt;
      v_normals_cyl1[cyl1_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl1[cyl1_idx] = glm::vec2(longs/(2*PI),lats/height);
      cyl1_idx++;

      if (lats + 0.01 > 0.2)
        l = 0.2;
      else
        l = lats + 0.01;
      x = r * cos(longs);
      y = l;
      z = r * sin(longs);
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_cyl1[cyl1_idx] = color;
      v_positions_cyl1[cyl1_idx] = pt;
      v_normals_cyl1[cyl1_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl1[cyl1_idx] = glm::vec2(longs/(2*PI),l/height);
      cyl1_idx++;
    }
  }
}

void con1(double radius, int Lats, int height)
{
  float lats, longs;
  float r;
  float inc = 0.01;

  float slices = (180 / (float(Lats) * 10)) / 2;

  float l;

  for (lats = 0.0; lats <= height * 0.5; lats += inc) // 1 to 1+height
  {
    r = radius * (1 - lats / height);
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = r * cos(longs);
      float y = lats;
      float z = r * sin(longs);
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_con1[con1_idx] = white;
      v_positions_con1[con1_idx] = pt;
      v_normals_con1[con1_idx] = pt;
      tex_coords_con1[con1_idx] = glm::vec2(longs/(2*PI),lats/height);
      con1_idx++;

      if (lats + inc > height*0.5)
        l = height*0.5;
      else
        l = lats + inc;
      x = r * cos(longs);
      y = l;
      z = r * sin(longs);
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_con1[con1_idx] = white;
      v_positions_con1[con1_idx] = pt;
      v_normals_con1[con1_idx] = pt;
      tex_coords_con1[con1_idx] = glm::vec2(longs/(2*PI),l/height);
      con1_idx++;
    }
  }

  r = 0.25;

  for (lats = 0; lats <= PI/2; lats += inc)
  {
    r = 0.25;
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = r * sin(lats) * cos(longs);
      float y = r * cos(lats);
      float z = r * sin(lats) * sin(longs);
      y += 0.45;
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_con1[con1_idx] = white;
      v_positions_con1[con1_idx] = pt;
      v_normals_con1[con1_idx] = pt;
      tex_coords_con1[con1_idx] = glm::vec2(longs/(2*PI),(y+0.45)/height);
      con1_idx++;

      if (lats + inc > 1.0 + height)
        l = 1.0 + height;
      else
        l = lats + inc;
      x = r * sin(l) * cos(longs);
      y = r * cos(l);
      z = r * sin(l) * sin(longs);
      y += 0.45;
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_con1[con1_idx] = white;
      v_positions_con1[con1_idx] = pt;
      v_normals_con1[con1_idx] = pt;
      tex_coords_con1[con1_idx] = glm::vec2(longs/(2*PI),(y+0.45)/height);
      con1_idx++;
    }
  }
}

void cyl2(double radius, int Lats, int height)
{
  float lats, longs;

  float slices = (180 / (float(Lats) * 10)) / 2;

  float l;

  for (lats = 0.0; lats <= height; lats += 0.1)
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * cos(longs);
      float y = lats;
      float z = radius * sin(longs);
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_cyl2[cyl2_idx] = color;
      v_positions_cyl2[cyl2_idx] = pt;
      v_normals_cyl2[cyl2_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl2[cyl2_idx] = glm::vec2(longs/(2*PI),y/height);
      cyl2_idx++;

      if (lats + 0.1 > height)
        l = height;
      else
        l = lats + 0.1;
      x = radius * cos(longs);
      y = l;
      z = radius * sin(longs);
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_cyl2[cyl2_idx] = color;
      v_positions_cyl2[cyl2_idx] = pt;
      v_normals_cyl2[cyl2_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl2[cyl2_idx] = glm::vec2(longs/(2*PI),y/height);
      cyl2_idx++;
    }
  }
}

void cyl3(double radius, int Lats, int height)
{
  height = 4.0;

  float lats, longs;

  float slices = (180 / (float(Lats) * 10)) / 2;

  float l;

  for (lats = 3.0; lats <= 4.0; lats += 0.1) // -3.0 to -2.0
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * cos(longs);
      float y = lats;
      float z = radius * sin(longs);
      glm::vec4 pt(x, y, z, 1.0);

      v_colors_cyl3[cyl3_idx] = color;
      v_positions_cyl3[cyl3_idx] = pt;
      v_normals_cyl3[cyl3_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl3[cyl3_idx] = glm::vec2(longs/(2*PI),lats/height);
      cyl3_idx++;

      if (lats + 0.1 > 4.0)
        l = 4.0;
      else
        l = lats + 0.1;
      x = radius * cos(longs);
      y = l;
      z = radius * sin(longs);
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_cyl3[cyl3_idx] = color;
      v_positions_cyl3[cyl3_idx] = pt;
      v_normals_cyl3[cyl3_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl3[cyl3_idx] = glm::vec2(longs/(2*PI),l/height);
      cyl3_idx++;
    }
  }

  for (lats = 0.0; lats <= 3.0; lats += 0.1) // -6.0 to -3.0
  {
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = radius * cos(longs);
      float y = lats;
      float z = radius * sin(longs);
      glm::vec4 pt(x, y, z, 1.0);
      if(y<=-5.5) v_colors_cyl3[cyl3_idx] = color;
      else v_colors_cyl3[cyl3_idx] = white;
      v_positions_cyl3[cyl3_idx] = pt;
      v_normals_cyl3[cyl3_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl3[cyl3_idx] = glm::vec2(longs/(2*PI),lats/height);
      cyl3_idx++;

      if (lats + 0.1 > 3.0)
        l = 3.0;
      else
        l = lats + 0.1;
      x = radius * cos(longs);
      y = l;
      z = radius * sin(longs);
      pt = glm::vec4(x, y, z, 1.0);
      if(y<=-5.5) v_colors_cyl3[cyl3_idx] = color;
      else v_colors_cyl3[cyl3_idx] = white;
      v_positions_cyl3[cyl3_idx] = pt;
      v_normals_cyl3[cyl3_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl3[cyl3_idx] = glm::vec2(longs/(2*PI),l/height);
      cyl3_idx++;
    }
  }

  for (lats = -0.3; lats <= 0.0; lats += 0.01)
  {
    double r = 0.4-(lats+0.5)*0.5;
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = r * cos(longs);
      float y = lats;
      float z = r * sin(longs);
      glm::vec4 pt(x, y, z, 1.0);
      v_colors_cyl3[cyl3_idx] = color;
      v_positions_cyl3[cyl3_idx] = pt;
      v_normals_cyl3[cyl3_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl3[cyl3_idx] = glm::vec2(longs/(2*PI),lats/height);
      cyl3_idx++;

      if (lats + 0.01 > 0.0)
        l = 0.0;
      else
        l = lats + 0.01;
      x = r * cos(longs);
      y = l;
      z = r * sin(longs);
      pt = glm::vec4(x, y, z, 1.0);
      v_colors_cyl3[cyl3_idx] = color;
      v_positions_cyl3[cyl3_idx] = pt;
      v_normals_cyl3[cyl3_idx] = glm::vec4(x,y,0,1);
      tex_coords_cyl3[cyl3_idx] = glm::vec2(longs/(2*PI),l/height);
      cyl3_idx++;
    }
  }
}

void prop(double radius, int Lats, glm::vec3 v, float height)
{
  float lats, longs;
  float r;
  float inc = 0.01;

  float slices = (180 / (float(Lats) * 10)) / 2;

  float l;


  for (lats = 3.1; lats >= 2.8; lats -= inc) // -3.2 to -3.5
  {
    r = radius - radius*(lats-2.8)/0.3;
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = r * cos(longs);
      float y = lats;
      float z = r * sin(longs);
      glm::vec4 pt(glm::vec3(x, y, z)+v, 1.0);

      v_colors_prop[prop_idx] = color;
      v_positions_prop[prop_idx] = pt;
      v_normals_prop[prop_idx] = pt;
      tex_coords_prop[prop_idx] = glm::vec2(longs/(2*PI),lats/height);
      prop_idx++;

      if (lats + inc < 2.8)
        l = 2.8;
      else
        l = lats + inc;
      x = r * cos(longs);
      y = l;
      z = r * sin(longs);
      pt = glm::vec4(glm::vec3(x, y, z)+v, 1.0);
      v_colors_prop[prop_idx] = color;
      v_positions_prop[prop_idx] = pt;
      v_normals_prop[prop_idx] = pt;
      tex_coords_prop[prop_idx] = glm::vec2(longs/(2*PI),l/height);
      prop_idx++;
    }
  }

  for (lats = 2.8; lats >= 0.3; lats -= inc) // -3.5 to -6.0
  {
    r = radius;
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = r * cos(longs);
      float y = lats;
      float z = r * sin(longs);
      glm::vec4 pt(glm::vec3(x, y, z)+v, 1.0);

      v_colors_prop[prop_idx] = white;
      v_positions_prop[prop_idx] = pt;
      v_normals_prop[prop_idx] = glm::vec4(x,y,0,1);
      tex_coords_prop[prop_idx] = glm::vec2(longs/(2*PI),lats/height);
      prop_idx++;

      if (lats + inc < 0.3)
        l = 0.3;
      else
        l = lats + inc;
      x = r * cos(longs);
      y = l;
      z = r * sin(longs);
      pt = glm::vec4(glm::vec3(x, y, z)+v, 1.0);
      v_colors_prop[prop_idx] = white;
      v_positions_prop[prop_idx] = pt;
      v_normals_prop[prop_idx] = glm::vec4(x,y,0,1);
      tex_coords_prop[prop_idx] = glm::vec2(longs/(2*PI),l/height);
      prop_idx++;
    }
  }

  for (lats = 0.3; lats >= 0.0; lats -= inc) // -6.0 to -6.3
  {
    r = radius - (lats)*radius*2;
    for (longs = 0.0; longs <= 2.0 * PI; longs += slices)
    {
      float x = r * cos(longs);
      float y = lats;
      float z = r * sin(longs);
      glm::vec4 pt(glm::vec3(x, y, z)+v, 1.0);

      v_colors_prop[prop_idx] = color;
      v_positions_prop[prop_idx] = pt;
      v_normals_prop[prop_idx] = pt;
      tex_coords_prop[prop_idx] = glm::vec2(longs/(2*PI),lats/height);
      prop_idx++;

      if (lats + inc < 0.0)
        l = 0.0;
      else
        l = lats + inc;
      x = r * cos(longs);
      y = l;
      z = r * sin(longs);
      pt = glm::vec4(glm::vec3(x, y, z)+v, 1.0);
      v_colors_prop[prop_idx] = color;
      v_positions_prop[prop_idx] = pt;
      v_normals_prop[prop_idx] = pt;
      tex_coords_prop[prop_idx] = glm::vec2(longs/(2*PI),l/height);
      prop_idx++;
    }
  }

}

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("src/pslv_rocket/07_vshader_tex.glsl");
  std::string fragment_shader_file("src/pslv_rocket/07_fshader_tex.glsl");

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

  GLuint tex_prop=LoadTexture("src/pslv_rocket/images/prop1.bmp",200,200);
  GLuint tex_con1=LoadTexture("src/pslv_rocket/images/con1.bmp",481,336);
  GLuint tex_cyl1=LoadTexture("src/pslv_rocket/images/cyl1.bmp",450,253);
  GLuint tex_cyl2=LoadTexture("src/pslv_rocket/images/cyl2.bmp",450,422);
  GLuint tex_cyl3=LoadTexture("src/pslv_rocket/images/cyl3.bmp",2560,1440);
  GLuint tex_prop2=LoadTexture("src/pslv_rocket/images/prop2.bmp",275,183);

  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  Lat = tesselation;
  Long = tesselation;
  cyl1(Radius, Long, 1);
  
  con1(Radius, Long, 1);

  cyl2(0.4, Long, 2);

  cyl3(0.4, Long, 1);

  for(int i=-1;i<=1;i++){
    double theta = (PI/3)*i;
    prop(0.2, Long, glm::vec3(0.6*cos(theta), 0.0, 0.6*sin(theta)), 3.1);
    prop(0.2, Long, glm::vec3(-0.6*cos(theta), 0.0, 0.6*sin(theta)), 3.1);
  }

  //note that the buffers are initialized in the respective constructors
  node1 = new csX75::HNode(NULL, num_vertices, v_positions_cyl1, v_colors_cyl1, v_normals_cyl1, tex_coords_cyl1, sizeof(v_positions_cyl1), sizeof(v_colors_cyl1), sizeof(v_normals_cyl1), sizeof(tex_coords_cyl1), false, tex_cyl1);
  node1->change_parameters(0.0, 0.0, 0.0, 0.0, 110.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_con1, v_colors_con1, v_normals_con1, tex_coords_cyl1, sizeof(v_positions_con1), sizeof(v_colors_con1), sizeof(v_normals_con1), sizeof(tex_coords_cyl1), false, tex_prop);
  node2->change_parameters(0.0, 1.2, 0.0, 0.0, 0.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_cyl2, v_colors_cyl2, v_normals_cyl2, tex_coords_cyl2, sizeof(v_positions_cyl2), sizeof(v_colors_cyl2), sizeof(v_normals_cyl2), sizeof(tex_coords_cyl2), false, tex_cyl2);
  node2->change_parameters(0.0, -1.2, 0.0, 0.0, 0.0, 0.0);
  node2 = new csX75::HNode(node2, num_vertices, v_positions_cyl3, v_colors_cyl3, v_normals_cyl3, tex_coords_cyl1, sizeof(v_positions_cyl3), sizeof(v_colors_cyl3), sizeof(v_normals_cyl3), sizeof(tex_coords_cyl1), false, tex_cyl3);
  node2->change_parameters(0.0, -4.0, 0.0, 0.0, 0.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices2, v_positions_prop, v_colors_prop, v_normals_prop, tex_coords_prop, sizeof(v_positions_prop), sizeof(v_colors_prop), sizeof(v_normals_prop), sizeof(tex_coords_prop), false, tex_prop2);
  node2->change_parameters(0.0, -5.5, 0.0, 0.0, 0.0, 0.0);
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
