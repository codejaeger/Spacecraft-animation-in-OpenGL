#include "a3-scene.hpp"
#include "texture.cpp"

double PI = 3.14159265;
GLuint shaderProgram;
GLuint vbo_box[2], vao_box[2];
GLuint vbo_solar[2], vao_solar[2];
GLuint vbo_refl[2], vao_refl[2];
GLuint tex;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c1_rotation_matrix;
glm::mat4 c2_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;
glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;

GLuint uModelViewMatrix;
GLuint viewMatrix;
GLuint normalMatrix;
GLuint texCoord;

glm::mat4 scale[4], rot[4], trans[4];

int count = 0;

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

void load_earth(std::string filename){
  std::ifstream infile;
  infile.open(filename);
    infile>>earth_idx;
    // std::cout<<filename<<"\n";
  for(int i=0;i<earth_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_earth[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_earth[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_earth[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_earth[i][j];
  }

  infile>>space_idx;
  for(int i=0;i<space_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_space[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_space[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_space[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_space[i][j];
  }

  infile.close();
  std::cout<<"Model loaded successfully"<<"\n";

  GLuint tex_earth = LoadTexture("src/main_file/images/2k_earth_daymap.bmp", 2048, 1024);
  GLuint tex_space = LoadTexture("src/main_file/images/space1.bmp", 800, 800);
  // glBindTexture(GL_TEXTURE_2D, tex1);

  node4 = new csX75::HNode(NULL, num_vertices, v_positions_earth, v_colors_earth, v_normals_earth, tex_coords_earth, sizeof(v_positions_earth), sizeof(v_colors_earth), sizeof(v_normals_earth), sizeof(tex_coords_earth), false, tex_earth);
  node12 = new csX75::HNode(node4, num_vertices, v_positions_space, v_colors_space, v_normals_space, tex_coords_space, sizeof(v_positions_space), sizeof(v_colors_space), sizeof(v_normals_space), sizeof(tex_coords_space), false, tex_space);
  // root_node = curr_node = node1;
  // root_node = curr_node = node7;
}

void load_payload(std::string filename){
  // std::string filepath = "../model/model_payload.raw";
  // std::cout<<filename<<"\n";
  std::ifstream infile;
  infile.open(filename);
  infile>>box_idx;
  for(int i=0;i<box_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_box[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_box[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_box[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_box[i][j];
  }

  infile>>prop_idx;
  for(int i=0;i<prop_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_prop[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_prop[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_prop[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_prop[i][j];
  }

  infile>>solar_idx;
  for(int i=0;i<solar_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_solar[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_solar[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_solar[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_solar[i][j];
  }

  infile>>refl_idx;
  for(int i=0;i<refl_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_refl[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_refl[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_refl[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_refl[i][j];
  }

  infile>>extra_idx;
  for(int i=0;i<extra_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_extra[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_extra[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_extra[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_extra[i][j];
  }

  infile.close();
  std::cout<<"Model loaded successfully"<<"\n";

  GLuint tex1=LoadTexture("src/main_file/images/launchpad1.bmp",2047,2047);
  GLuint tex2=LoadTexture("src/main_file/images/launchpad2.bmp",408,236);
  GLuint tex_solar=LoadTexture("src/main_file/images/solar2.bmp",390,220);
  GLuint tex_refl = LoadTexture("src/main_file/images/refl1.bmp",1800,1734);
  GLuint tex_prop = LoadTexture("src/main_file/images/refl1.bmp",1800,1734);
  GLuint tex_box = LoadTexture("src/main_file/images/box1.bmp",1300,1300);
  GLuint tex_extra = LoadTexture("src/main_file/images/extra.bmp",450,422);
  glBindTexture(GL_TEXTURE_2D, tex1);

  node7 = new csX75::HNode(NULL, num_vertices, v_positions_box, v_colors_box, v_normals_box, tex_coords_box, sizeof(v_positions_box), sizeof(v_colors_box), sizeof(v_normals_box), sizeof(tex_coords_box), false, tex_box);
  node8 = new csX75::HNode(node7, num_vertices, v_positions_prop, v_colors_prop, v_normals_prop, tex_coords_prop, sizeof(v_positions_prop), sizeof(v_colors_prop), sizeof(v_normals_prop), sizeof(tex_coords_prop), false, tex_prop);
  node8->change_parameters(0.0, -1.0, 0.0, 0.0, 0.0, 0.0);
  node8 = new csX75::HNode(node7, num_vertices, v_positions_extra, v_colors_extra, v_normals_extra, tex_coords_extra, sizeof(v_positions_extra), sizeof(v_colors_extra), sizeof(v_normals_extra), sizeof(tex_coords_extra), false, tex_extra);
  node8->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  node8 = new csX75::HNode(node7, num_vertices, v_positions_solar, v_colors_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_colors_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false, tex_solar);
  node8->change_parameters(-1.1, 0.0, -1.0, 0.0, 0.0, 0.0);
  node9 = new csX75::HNode(node8, num_vertices, v_positions_solar, v_colors_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_colors_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false, tex_solar);
  node9->change_parameters(0.0, 0.0, -0.1, 0.0, 0.0, 0.0);
  node10 = new csX75::HNode(node8, num_vertices, v_positions_solar, v_colors_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_colors_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false, tex_solar);
  node10->change_parameters(0.0, 0.0, 2.1, 0.0, 180.0, 0.0);
  node11 = new csX75::HNode(node7, num_vertices, v_positions_refl, v_colors_refl, v_normals_refl, tex_coords_refl, sizeof(v_positions_refl), sizeof(v_colors_refl), sizeof(v_normals_refl), sizeof(tex_coords_refl), false, tex_refl);
  node11->change_parameters(1.1, -1.0, 0.0, 0.0, 0.0, 0.0);
  // root_node = curr_node = node7;
}

// int box_idx = 0;
// glm::vec4 v_positions_box[num_vertices];
// glm::vec4 v_colors_box[num_vertices];
// glm::vec4 v_normals_box[num_vertices];

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

void load_launchpad(std::string filename){
  // box_idx = 0;
  // std::string filepath = "../model/model_launchpad.raw";
  std::ifstream infile;
  infile.open(filename);
  infile>>box_idx;
  for(int i=0;i<box_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_box[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_box[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_box[i][j];
    // for(int j=0;j<2;j++) infile>>tex_coords_box[i][j];
  }

  infile>>plat_idx;
  for(int i=0;i<plat_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_plat[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_plat[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_plat[i][j];
    // for(int j=0;j<2;j++) infile>>tex_coords_prop[i][j];
  }

  infile>>w1_idx;
  for(int i=0;i<w1_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_w1[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_w1[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_w1[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_w1[i][j];
  }

  infile>>w2_idx;
  for(int i=0;i<w2_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_w2[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_w2[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_w2[i][j];
    // for(int j=0;j<2;j++) infile>>tex_coords_w2[i][j];
  }

  infile>>w3_idx;
  for(int i=0;i<w3_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_w3[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_w3[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_w3[i][j];
    // for(int j=0;j<2;j++) infile>>tex_coords_w3[i][j];
  }

  infile.close();
  std::cout<<"Model loaded successfully"<<"\n";

  GLuint tex1=LoadTexture("src/main_file/images/launchpad1.bmp",2047,2047);
  GLuint tex2=LoadTexture("src/main_file/images/launchpad2.bmp",408,236);
  // tex=LoadTexture("src/main_file/images/all1.bmp",256,256);
  // glBindTexture(GL_TEXTURE_2D, tex);

  //note that the buffers are initialized in the respective constructors
  node1 = new csX75::HNode(NULL, num_vertices, v_positions_w1, v_colors_w1, v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_colors_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false, tex2);
  node1->change_parameters(2.0, -3.0, 0.0, 0.0, 0.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_w1, v_colors_w1, v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_colors_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false, tex2);
  node2->change_parameters(-0.75, 0.0, -1.25, 0.0, 90.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_w1, v_colors_w1, v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_colors_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false, tex2);
  node2->change_parameters(-0.75, 0.0, 1.25, 0.0, 90.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, v_positions_plat, v_colors_plat, v_normals_plat, tex_coords_w1, sizeof(v_positions_plat), sizeof(v_colors_plat), sizeof(v_normals_plat), sizeof(tex_coords_w1), false, tex1);
  node2->change_parameters(-1.75, 0.25, 0.0, 0.0, 0.0, 0.0);
  node3 = new csX75::HNode(node2, num_vertices, v_positions_box, v_colors_box, v_normals_box, tex_coords_w1, sizeof(v_positions_box), sizeof(v_colors_box), sizeof(v_normals_box), sizeof(tex_coords_w1), true, tex1);
  node3->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  root_node = curr_node = node1;
}

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

int prop1_idx = 0;
const int num_vertices2 = 200000;
glm::vec4 v_positions_prop1[num_vertices2];
glm::vec4 v_colors_prop1[num_vertices2];
glm::vec4 v_normals_prop1[num_vertices2];
glm::vec2 tex_coords_prop1[num_vertices2];

void load_rocket(std::string filename){
  // box_idx = 0;
  // std::string filepath = filename;
  std::ifstream infile;
  infile.open(filename);
  infile>>cyl1_idx;
  for(int i=0;i<cyl1_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_cyl1[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_cyl1[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_cyl1[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_cyl1[i][j];
  }

  infile>>con1_idx;
  for(int i=0;i<con1_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_con1[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_con1[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_con1[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_con1[i][j];
  }

  infile>>cyl2_idx;
  for(int i=0;i<cyl2_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_cyl2[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_cyl2[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_cyl2[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_cyl2[i][j];
  }

  infile>>cyl3_idx;
  for(int i=0;i<cyl3_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_cyl3[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_cyl3[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_cyl3[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_cyl3[i][j];
  }

  infile>>prop1_idx;
  for(int i=0;i<prop1_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_prop1[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_prop1[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_prop1[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_prop1[i][j];
  }

  infile.close();
  std::cout<<"Model loaded successfully"<<"\n";

  GLuint tex_prop=LoadTexture("src/main_file/images/prop1.bmp",200,200);
  GLuint tex_con1=LoadTexture("src/main_file/images/con1.bmp",481,336);
  GLuint tex_cyl1=LoadTexture("src/main_file/images/cyl1.bmp",450,253);
  GLuint tex_cyl2=LoadTexture("src/main_file/images/cyl2.bmp",450,422);
  GLuint tex_cyl3=LoadTexture("src/main_file/images/cyl3.bmp",2560,1440);
  GLuint tex_prop2=LoadTexture("src/main_file/images/prop2.bmp",275,183);

  //note that the buffers are initialized in the respective constructors
  node5 = new csX75::HNode(NULL, num_vertices, v_positions_cyl1, v_colors_cyl1, v_normals_cyl1, tex_coords_cyl1, sizeof(v_positions_cyl1), sizeof(v_colors_cyl1), sizeof(v_normals_cyl1), sizeof(tex_coords_cyl1), false, tex_cyl1);
  node5->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  node6 = new csX75::HNode(node5, num_vertices, v_positions_con1, v_colors_con1, v_normals_con1, tex_coords_cyl1, sizeof(v_positions_con1), sizeof(v_colors_con1), sizeof(v_normals_con1), sizeof(tex_coords_cyl1), false, tex_prop);
  node6->change_parameters(0.0, 1.2, 0.0, 0.0, 0.0, 0.0);
  node6 = new csX75::HNode(node5, num_vertices, v_positions_cyl2, v_colors_cyl2, v_normals_cyl2, tex_coords_cyl2, sizeof(v_positions_cyl2), sizeof(v_colors_cyl2), sizeof(v_normals_cyl2), sizeof(tex_coords_cyl2), false, tex_cyl2);
  node6->change_parameters(0.0, -1.2, 0.0, 0.0, 0.0, 0.0);
  node6 = new csX75::HNode(node5, num_vertices, v_positions_cyl3, v_colors_cyl3, v_normals_cyl3, tex_coords_cyl1, sizeof(v_positions_cyl3), sizeof(v_colors_cyl3), sizeof(v_normals_cyl3), sizeof(tex_coords_cyl1), false, tex_cyl3);
  node6->change_parameters(0.0, -4.0, 0.0, 0.0, 0.0, 0.0);
  node6 = new csX75::HNode(node5, num_vertices2, v_positions_prop1, v_colors_prop1, v_normals_prop1, tex_coords_prop1, sizeof(v_positions_prop1), sizeof(v_colors_prop1), sizeof(v_normals_prop1), sizeof(tex_coords_prop1), false, tex_prop2);
  node6->change_parameters(0.0, -4.0, 0.0, 0.0, 0.0, 0.0);
  // root_node = curr_node = node11;
}

void load_scn_file(void){
  std::string filepath = "data/launch.scn";
  std::ifstream infile;
  infile.open(filepath);
  
  for(int i=0;i<3;i++){
    std::string filename;
    infile>>filename;
    if(i==0) load_earth(filename);
    else if(i==1) load_launchpad(filename);
    else if(i==2) load_rocket(filename);
    else load_payload(filename);
    
    GLfloat a, b, c;
    infile>>a>>b>>c;
    scale[i] = glm::scale(glm::mat4(1.0),glm::vec3(a,b,c));
    
    infile>>a>>b>>c;
    rot[i] = glm::rotate(glm::mat4(1.0),glm::radians(a),glm::vec3(1,0,0));
    rot[i] = glm::rotate(rot[i],glm::radians(b),glm::vec3(0,1,0));
    rot[i] = glm::rotate(rot[i],glm::radians(c),glm::vec3(0,0,1));

    infile>>a>>b>>c;
    trans[i] = glm::translate(glm::mat4(1.0),glm::vec3(a,b,c));
  }
}

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("src/main_file/07_vshader_tex.glsl");
  std::string fragment_shader_file("src/main_file/07_fshader_tex.glsl");

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

  //note that the buffers are initialized in the respective constructors
  load_scn_file();
  
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  // glm::vec3 rocket_pos(1.0);
  glm::vec3 rocket_pos = glm::vec3(trans[2]*rot[2]*scale[2]*glm::vec4(node5->tx,node5->ty,node5->tz,1.0));

  //Creating the lookat and the up vectors for the camera
  if(camera==1){
    c1_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c1_xrot), glm::vec3(1.0f, 0.0f, 0.0f));
    c1_rotation_matrix = glm::rotate(c1_rotation_matrix, glm::radians(c1_yrot), glm::vec3(0.0f, 1.0f, 0.0f));
    c1_rotation_matrix = glm::rotate(c1_rotation_matrix, glm::radians(c1_zrot), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec4 c1_pos = glm::vec4(c1_xpos, c1_ypos, c1_zpos, 1.0) * c1_rotation_matrix;
    glm::vec4 c1_up = glm::vec4(c1_up_x, c1_up_y, c1_up_z, 1.0) * c1_rotation_matrix;
    //Creating the lookat matrix
    lookat_matrix = glm::lookAt(glm::vec3(c1_pos), rocket_pos, glm::vec3(c1_up));
  }
  else{
    c2_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c2_xrot), glm::vec3(1.0f, 0.0f, 0.0f));
    c2_rotation_matrix = glm::rotate(c2_rotation_matrix, glm::radians(c2_yrot), glm::vec3(0.0f, 1.0f, 0.0f));
    c2_rotation_matrix = glm::rotate(c2_rotation_matrix, glm::radians(c2_zrot), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec4 c2_pos = glm::vec4(c2_xpos, c2_ypos, c2_zpos, 1.0) * c2_rotation_matrix;
    glm::vec4 c2_up = glm::vec4(c2_up_x, c2_up_y, c2_up_z, 1.0) * c2_rotation_matrix;
    //Creating the lookat matrix
    // lookat_matrix = glm::lookAt(glm::vec3(c2_pos), glm::vec3(-0.09,0.22,1.0), glm::vec3(c2_up));
    lookat_matrix = glm::lookAt(glm::vec3(c2_pos), rocket_pos, glm::vec3(c2_up));
    
  }

  //creating the projection matrix
  if (enable_perspective)
    projection_matrix = glm::frustum(-0.01, 0.01, -0.01, 0.01, 0.01, 10.0);
  //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-3.0, 3.0, -3.0, 3.0, -5.0, 5.0);

  view_matrix = projection_matrix * lookat_matrix;

  // modelview_matrix = view_matrix * model_matrix;
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // normal_matrix = glm::transpose(glm::inverse(glm::mat3(modelview_matrix)));
  // glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

  matrixStack.push_back(view_matrix*trans[0]*rot[0]*scale[0]);
  node4->render_tree();
  matrixStack.pop_back();

  matrixStack.push_back(view_matrix*trans[1]*rot[1]*scale[1]);
  node1->render_tree();
  matrixStack.pop_back();

  matrixStack.push_back(view_matrix*trans[2]*rot[2]*scale[2]);
  node5->render_tree();
  matrixStack.pop_back();

  if(animation){
    if(count<400){
      node2->tx -= 0.01;
      // node2->ty -= 0.01;
      node5->tx -= 0.01;
      // node5->ty -= 0.01;
      node2->update_matrices();
      node5->update_matrices();
      count++;
    }
    else{
      node5->ty += 0.05;
      node5->update_matrices();
    }
  }

  // matrixStack.push_back(view_matrix*trans[3]*rot[3]*scale[3]);
  // node7->render_tree();
  // matrixStack.pop_back();
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
