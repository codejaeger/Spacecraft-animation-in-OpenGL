#include "a3-scene.hpp"
#include "texture.cpp"
#include <bits/stdc++.h>

double PI = 3.14159265;
GLuint shaderProgram;
GLuint vbo_box[2], vao_box[2];
GLuint vbo_solar[2], vao_solar[2];
GLuint vbo_refl[2], vao_refl[2];
GLuint tex;
GLuint uniformTex0,uniformTex1;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 ortho_matrix;
glm::mat4 c1_rotation_matrix;
glm::mat4 c2_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;
glm::mat4 modelview_matrix;
glm::mat4 normal_matrix;

GLuint uModelViewMatrix;
// GLuint viewMatrix;
GLuint normalMatrix;
GLuint texCoord;
GLuint modelMatrix;
int sig=0;


glm::mat4 scale[4], rot[4], trans[4];
 
glm::vec3 cur_cent=glm::vec3(1.0,1.0,1.0);
const int tess_curs = 10;
const int curs_ver = 40;
glm::vec4 v_positions_cursor[curs_ver];
glm::vec4 v_normals_cursor[curs_ver];
glm::vec3 v_tex_cursor[curs_ver];


glm::vec4 v_positions_bez_line[10000];
glm::vec3 v_tex_line[10000];
glm::vec4 v_tex_norms[10000];

int line_idx=0;

const int max_num_ctrl_pnts=100;
glm::vec3 bez_ctrl[max_num_ctrl_pnts];
int bez_idx = 0;

int count = 0;

//-----------------------------------------------------------------

const int num_vertices = 100000;



int tri_idx = 0;
glm::vec4 v_positions[num_vertices];
glm::vec4 v_normals[num_vertices];
glm::vec3 tex_coords[num_vertices];

int trii = 0;
glm::vec4 spv_positions[num_vertices];
glm::vec4 spv_normals[num_vertices];
glm::vec3 sptex_coords[num_vertices];

int tric = 0;
glm::vec4 cpv_positions[num_vertices];
glm::vec4 cpv_normals[num_vertices];
glm::vec3 cptex_coords[num_vertices];

int trisun = 0;
glm::vec4 sv_positions[num_vertices];
glm::vec4 sv_normals[num_vertices];
glm::vec3 stex_coords[num_vertices];

int trimars = 0;
glm::vec4 mrsv_positions[num_vertices];
glm::vec4 mrsv_normals[num_vertices];
glm::vec3 mrstex_coords[num_vertices];



int box_idx = 0;
glm::vec4 v_positions_box[num_vertices];
glm::vec4 v_colors_box[num_vertices];
glm::vec4 v_normals_box[num_vertices];
glm::vec3 tex_coords_box[num_vertices];

int prop_idx = 0;
glm::vec4 v_positions_prop[num_vertices];
glm::vec4 v_colors_prop[num_vertices];
glm::vec4 v_normals_prop[num_vertices];
glm::vec3 tex_coords_prop[num_vertices];

int solar_idx = 0;
glm::vec4 v_positions_solar[num_vertices];
glm::vec4 v_colors_solar[num_vertices];
glm::vec4 v_normals_solar[num_vertices];
glm::vec3 tex_coords_solar[num_vertices];

int refl_idx = 0;
glm::vec4 v_positions_refl[num_vertices];
glm::vec4 v_colors_refl[num_vertices];
glm::vec4 v_normals_refl[num_vertices];
glm::vec3 tex_coords_refl[num_vertices];

int extra_idx = 0;
glm::vec4 v_positions_extra[num_vertices];
glm::vec4 v_colors_extra[num_vertices];
glm::vec4 v_normals_extra[num_vertices];
glm::vec3 tex_coords_extra[num_vertices];



// void cal_bezier(float tess)
// {
//   bez_idx=0;
//   for(int j=0;j<bez_ctrl_idx;j+=3)
//   {
//   for(GLfloat i=0;i<1;i+=1.0/tess)
//   {
//     glm::vec3 p0 = bez_ctrl[j],p1 = bez_ctrl[j+1],p2 = bez_ctrl[j+2]; 
//     glm::vec3 pt = GLfloat(pow((1-i),2))*p0 + GLfloat(2*pow((1-i),1)*i)*p1 + GLfloat(pow(i,2))*p2;
//     bezier[bez_idx]=pt;
//     bez_idx++;
//   }
//   } 
// }

void update_bez_curve(void){
  // bez_ctrl bez_idx v_positions_bez_line
  int n = bez_idx;
  glm::vec3 B[100][100];
  for(int j=0;j<n;j++){
    B[0][j] = bez_ctrl[j];
  }
  std::cout<<n<<"\n";
  // for(int i=0;i<n;i++){
  //   for(int j=0;j<3;j++){
  //     std::cout<<bez_ctrl[i][j]<<" ";
  //   }
  //   std::cout<<"\n";
  // }
  int k=0;
  for(float t=0.0;t<=1.0;t+=0.01){
    for(int i=1;i<n;i++){
      for(int j=0;j<=n-i;j++){
        B[i][j] = B[i-1][j]*(1-t) + B[i-1][j+1]*t;
      }
    }
    v_positions_bez_line[k] = glm::vec4(B[n-1][0],1);
    v_tex_line[k]=glm::vec3(0,0,5);
    v_tex_norms[k]=glm::vec4(0.0);
    k++;
  }
  // for(int i=0;i<100;i++){
  //   for(int j=0;j<4;j++){
  //     std::cout<<v_positions_bez_line[i][j]<<" ";
  //   }
  //   std::cout<<"\n";
  // }
  node_line = new csX75::HNode(NULL, 100, 0, 0, v_positions_bez_line, v_tex_norms, v_tex_line, sizeof(v_positions_bez_line), sizeof(v_tex_norms), sizeof(v_tex_line), true);
}


int cur_idx = 0;
void cursor(double radius, int Lats, int Longs)
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
      v_positions_cursor[cur_idx] = pt;
      v_normals_cursor[cur_idx] = norm;

      // Texture coordinates of a point //
      GLfloat u = longs / (2 * PI), v = 1 - lats / PI;
      v_tex_cursor[cur_idx] = glm::vec3(u, v,3);
      cur_idx++;
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
      v_positions_cursor[cur_idx] = pt;
      v_normals_cursor[cur_idx] = norm;
      u = longs / (2 * PI);
      v = 1 - l / PI;
      // // std::cout<<u<<" "<<v<<"\n";
      v_tex_cursor[cur_idx] = glm::vec3(u, v,3);
      cur_idx++;
    }
  }
}



void update_ctrl_pnts(int idx)
{
  glm::vec3 pn = bez_ctrl[idx-1];
  glm::vec3 p0 = bez_ctrl[0];
  GLuint texsun = LoadTexture("images/2k_sun.bmp", 2048, 1024);
  if(idx==1){
    // std::cout<<"here\n";
    bez_node = new csX75::HNode(NULL, curs_ver, texsun, texsun, v_positions_cursor, v_normals_cursor, v_tex_cursor, sizeof(v_positions_cursor), sizeof(v_normals_cursor), sizeof(v_tex_cursor), false);
    bez_node->change_parameters(p0[0],p0[1],p0[2],0,0,0);
  }
  else{
    new_node = new csX75::HNode(bez_node, curs_ver, texsun, texsun, v_positions_cursor, v_normals_cursor, v_tex_cursor, sizeof(v_positions_cursor), sizeof(v_normals_cursor), sizeof(v_tex_cursor), false);
    new_node->change_parameters(pn[0]-p0[0],pn[1]-p0[1],pn[2]-p0[2],0,0,0);
  }
}

void load_all_ctrl_pnts(){
  for(int i=1;i<=bez_idx;i++){
    update_ctrl_pnts(i);
  }
}

void load_earth(std::string filename){
  std::ifstream infile;
  infile.open(filename);
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

  GLuint texd = LoadTexture("images/2k_earth_daymap.bmp", 2048, 1024);
  GLuint texn = LoadTexture("images/2k_earth_nightmap.bmp", 2048, 1024);
  GLuint texc = LoadTexture("images/2k_earth_clouds.bmp", 2048, 1024);
  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, tex2);
  GLuint tex2 = LoadTexture("images/2k_stars_milky_way.bmp", 2048, 1024);
  GLuint texsun = LoadTexture("images/2k_sun.bmp", 2048, 1024);
  GLuint texmars = LoadTexture("images/2k_mars.bmp", 2048, 1024);


  // GLuint tex_earth = LoadTexture("./images/2k_earth_daymap.bmp", 2048, 1024);
  // GLuint tex_space = LoadTexture("./images/space1.bmp", 800, 800);
  // glBindTexture(GL_TEXTURE_2D, tex1);

  // node4 = new csX75::HNode(NULL, num_vertices, v_positions_earth, v_colors_earth, v_normals_earth, tex_coords_earth, sizeof(v_positions_earth), sizeof(v_colors_earth), sizeof(v_normals_earth), sizeof(tex_coords_earth), false, tex_earth);
  // node12 = new csX75::HNode(node4, num_vertices, v_positions_space, v_colors_space, v_normals_space, tex_coords_space, sizeof(v_positions_space), sizeof(v_colors_space), sizeof(v_normals_space), sizeof(tex_coords_space), false, tex_space);
  
  node1e = new csX75::HNode(NULL,num_vertices,texsun,texsun,sv_positions,sv_normals,stex_coords,sizeof(sv_positions),sizeof(sv_normals),sizeof(stex_coords),false);
  node1e->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  node2e = new csX75::HNode(node1e,num_vertices,texd,texn,v_positions,v_normals,tex_coords,sizeof(v_positions),sizeof(v_normals),sizeof(tex_coords),false);
  node2e->change_parameters(0,-3.0,0.0,0.0,0.0,0.0);
  node3e = new csX75::HNode(node1e,num_vertices,texmars,texmars,mrsv_positions,mrsv_normals,mrstex_coords,sizeof(mrsv_positions),sizeof(mrsv_normals),sizeof(mrstex_coords),false);
  node3e->change_parameters(0,-5.5,0,0.0,0.0,0.0);
  node4e = new csX75::HNode(node1e,num_vertices,tex2,tex2,spv_positions,spv_normals,sptex_coords,sizeof(spv_positions),sizeof(spv_normals),sizeof(sptex_coords),false);
  node5e = new csX75::HNode(node2e,num_vertices,texc,texc,cpv_positions,cpv_normals,cptex_coords,sizeof(cpv_positions),sizeof(cpv_normals),sizeof(cptex_coords),false);  


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
    // for(int j=0;j<2;j++) infile>>tex_coords_box[i][j];
    //   tex_coords_box[i][2]=0;
  }

  infile>>prop_idx;
  for(int i=0;i<prop_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_prop[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_prop[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_prop[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_prop[i][j];
      tex_coords_prop[i][2]=0;

  }

  infile>>solar_idx;
  for(int i=0;i<solar_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_solar[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_solar[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_solar[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_solar[i][j];
      tex_coords_solar[i][2]=0; 
  }

  infile>>refl_idx;
  for(int i=0;i<refl_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_refl[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_refl[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_refl[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_refl[i][j];
      tex_coords_refl[i][2]=0; 
  }

  infile>>extra_idx;
  for(int i=0;i<extra_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_extra[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_extra[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_extra[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_extra[i][j];
    tex_coords_extra[i][2]=0; 
  }

  infile.close();
  std::cout<<"Model loaded successfully"<<"\n";

  GLuint tex1=LoadTexture("./images/launchpad1.bmp",2047,2047);
  GLuint tex2=LoadTexture("./images/launchpad2.bmp",408,236);
  GLuint tex_solar=LoadTexture("./images/solar2.bmp",390,220);
  GLuint tex_refl = LoadTexture("./images/refl1.bmp",1800,1734);
  GLuint tex_prop = LoadTexture("./images/refl1.bmp",1800,1734);
  GLuint tex_box = LoadTexture("./images/box1.bmp",1300,1300);
  GLuint tex_extra = LoadTexture("./images/extra.bmp",450,422);
  glBindTexture(GL_TEXTURE_2D, tex1);

  node7 = new csX75::HNode(NULL, num_vertices, tex_box, tex_box, v_positions_box, v_normals_box, tex_coords_box, sizeof(v_positions_box), sizeof(v_normals_box), sizeof(tex_coords_box), false);
  node8 = new csX75::HNode(node7, num_vertices, tex_prop, tex_prop, v_positions_prop, v_normals_prop, tex_coords_prop, sizeof(v_positions_prop), sizeof(v_normals_prop), sizeof(tex_coords_prop), false);
  node8->change_parameters(0.0, -1.0, 0.0, 0.0, 0.0, 0.0);
  node8 = new csX75::HNode(node7, num_vertices, tex_extra, tex_extra, v_positions_extra, v_normals_extra, tex_coords_extra, sizeof(v_positions_extra), sizeof(v_normals_extra), sizeof(tex_coords_extra), false);
  node8->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  node8 = new csX75::HNode(node7, num_vertices, tex_solar, tex_solar, v_positions_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false);
  node8->change_parameters(-1.1, 0.0, -1.0, 0.0, 0.0, 0.0);
  node9 = new csX75::HNode(node8, num_vertices, tex_solar, tex_solar, v_positions_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false);
  node9->change_parameters(0.0, 0.0, -0.1, 0.0, 0.0, 0.0);
  node10 = new csX75::HNode(node8, num_vertices, tex_solar, tex_solar, v_positions_solar, v_normals_solar, tex_coords_solar, sizeof(v_positions_solar), sizeof(v_normals_solar), sizeof(tex_coords_solar), false);
  node10->change_parameters(0.0, 0.0, 2.1, 0.0, 180.0, 0.0);
  node11 = new csX75::HNode(node7, num_vertices, tex_refl, tex_refl, v_positions_refl, v_normals_refl, tex_coords_refl, sizeof(v_positions_refl), sizeof(v_normals_refl), sizeof(tex_coords_refl), false);
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
glm::vec3 tex_coords_w1[num_vertices];

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
    //   tex_coords_box[i][2]=3;
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
    for(int j=0;j<3;j++) infile>>tex_coords_w1[i][j];
      // tex_coords_w1[i][2] = 0;
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

  GLuint tex1=LoadTexture("./images/launchpad1.bmp",2047,2047);
  GLuint tex2=LoadTexture("./images/launchpad2.bmp",408,236);
  // tex=LoadTexture("./images/all1.bmp",256,256);
  // glBindTexture(GL_TEXTURE_2D, tex);

  //note that the buffers are initialized in the respective constructors
  node1 = new csX75::HNode(NULL, num_vertices, tex2, tex2, v_positions_w1, v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false);
  node1->change_parameters(2.0, -3.0, 0.0, 0.0, 0.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, tex2, tex2, v_positions_w1,  v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false);
  node2->change_parameters(-0.75, 0.0, -1.25, 0.0, 90.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, tex2, tex2, v_positions_w1,  v_normals_w1, tex_coords_w1, sizeof(v_positions_w1), sizeof(v_normals_w1), sizeof(tex_coords_w1), false);
  node2->change_parameters(-0.75, 0.0, 1.25, 0.0, 90.0, 0.0);
  node2 = new csX75::HNode(node1, num_vertices, tex1, tex1, v_positions_plat,  v_normals_plat, tex_coords_w1, sizeof(v_positions_plat),  sizeof(v_normals_plat), sizeof(tex_coords_w1), false);
  node2->change_parameters(-1.75, 0.25, 0.0, 0.0, 0.0, 0.0);
  node3 = new csX75::HNode(node2, num_vertices, tex1, tex1, v_positions_box,  v_normals_box, tex_coords_w1, sizeof(v_positions_box), sizeof(v_normals_box), sizeof(tex_coords_w1), true);
  node3->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  root_node = curr_node = node1;
}

int cyl1_idx = 0;
glm::vec4 v_positions_cyl1[num_vertices];
glm::vec4 v_colors_cyl1[num_vertices];
glm::vec4 v_normals_cyl1[num_vertices];
glm::vec3 tex_coords_cyl1[num_vertices];

int con1_idx = 0;
glm::vec4 v_positions_con1[num_vertices];
glm::vec4 v_colors_con1[num_vertices];
glm::vec4 v_normals_con1[num_vertices];
glm::vec3 tex_coords_con1[num_vertices];

int cyl2_idx = 0;
glm::vec4 v_positions_cyl2[num_vertices];
glm::vec4 v_colors_cyl2[num_vertices];
glm::vec4 v_normals_cyl2[num_vertices];
glm::vec3 tex_coords_cyl2[num_vertices];

int cyl3_idx = 0;
glm::vec4 v_positions_cyl3[num_vertices];
glm::vec4 v_colors_cyl3[num_vertices];
glm::vec4 v_normals_cyl3[num_vertices];
glm::vec3 tex_coords_cyl3[num_vertices];

int prop1_idx = 0;
const int num_vertices2 = 200000;
glm::vec4 v_positions_prop1[num_vertices2];
glm::vec4 v_colors_prop1[num_vertices2];
glm::vec4 v_normals_prop1[num_vertices2];
glm::vec3 tex_coords_prop1[num_vertices2];

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
      tex_coords_cyl1[i][2]=0;
  }

  infile>>con1_idx;
  for(int i=0;i<con1_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_con1[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_con1[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_con1[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_con1[i][j];
      tex_coords_con1[i][2]=0;
  }

  infile>>cyl2_idx;
  for(int i=0;i<cyl2_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_cyl2[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_cyl2[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_cyl2[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_cyl2[i][j];
      tex_coords_cyl2[i][2]=0;
  }

  infile>>cyl3_idx;
  for(int i=0;i<cyl3_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_cyl3[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_cyl3[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_cyl3[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_cyl3[i][j];
      tex_coords_cyl3[i][2]=0;
  }

  infile>>prop1_idx;
  for(int i=0;i<prop1_idx;i++){
    for(int j=0;j<4;j++) infile>>v_positions_prop1[i][j];
    for(int j=0;j<4;j++) infile>>v_colors_prop1[i][j];
    for(int j=0;j<4;j++) infile>>v_normals_prop1[i][j];
    for(int j=0;j<2;j++) infile>>tex_coords_prop1[i][j];
      tex_coords_prop1[i][2]=0;
  }

  infile.close();
  std::cout<<"Model loaded successfully"<<"\n";

  GLuint tex_prop=LoadTexture("./images/prop1.bmp",200,200);
  GLuint tex_con1=LoadTexture("./images/con1.bmp",481,336);
  GLuint tex_cyl1=LoadTexture("./images/cyl1.bmp",450,253);
  GLuint tex_cyl2=LoadTexture("./images/cyl2.bmp",450,422);
  GLuint tex_cyl3=LoadTexture("./images/cyl3.bmp",2560,1440);
  GLuint tex_prop2=LoadTexture("./images/prop2.bmp",275,183);

  //note that the buffers are initialized in the respective constructors
  node5 = new csX75::HNode(NULL, num_vertices, tex_cyl1, tex_cyl1, v_positions_cyl1, v_normals_cyl1, tex_coords_cyl1, sizeof(v_positions_cyl1), sizeof(v_normals_cyl1), sizeof(tex_coords_cyl1), false);
  node5->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
  node6 = new csX75::HNode(node5, num_vertices, tex_prop, tex_prop, v_positions_con1, v_normals_con1, tex_coords_cyl1, sizeof(v_positions_con1), sizeof(v_normals_con1), sizeof(tex_coords_cyl1), false);
  node6->change_parameters(0.0, 1.2, 0.0, 0.0, 0.0, 0.0);
  node6 = new csX75::HNode(node5, num_vertices, tex_cyl2, tex_cyl2, v_positions_cyl2, v_normals_cyl2, tex_coords_cyl2, sizeof(v_positions_cyl2),  sizeof(v_normals_cyl2), sizeof(tex_coords_cyl2), false);
  node6->change_parameters(0.0, -1.2, 0.0, 0.0, 0.0, 0.0);
  node6 = new csX75::HNode(node5, num_vertices, tex_cyl3, tex_cyl3, v_positions_cyl3,  v_normals_cyl3, tex_coords_cyl1, sizeof(v_positions_cyl3), sizeof(v_normals_cyl3), sizeof(tex_coords_cyl1), false);
  node6->change_parameters(0.0, -4.0, 0.0, 0.0, 0.0, 0.0);
  node6 = new csX75::HNode(node5, num_vertices2, tex_prop2, tex_prop2, v_positions_prop1,  v_normals_prop1, tex_coords_prop1, sizeof(v_positions_prop1), sizeof(v_normals_prop1), sizeof(tex_coords_prop1), false);
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
  // std::string vertex_shader_file("./07_vshader_tex.glsl");
  // std::string fragment_shader_file("./07_fshader_tex.glsl");


  cursor(0.1,tess_curs/5,tess_curs/5);

  std::string vertex_shader_file("a3_vshader.glsl");
  std::string fragment_shader_file("a3_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram(shaderProgram);

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation(shaderProgram, "vPosition");
  // vColor = glGetAttribLocation(shaderProgram, "vColor");
  vNormal = glGetAttribLocation(shaderProgram, "vNormal");
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
  uModelViewMatrix = glGetUniformLocation(shaderProgram, "uModelViewMatrix");
  normalMatrix = glGetUniformLocation(shaderProgram, "normalMatrix");
  // viewMatrix = glGetUniformLocation(shaderProgram, "viewMatrix");
  modelMatrix = glGetUniformLocation(shaderProgram, "modelMatrix");
  uniformTex0 = glGetUniformLocation( shaderProgram, "texturun" );
  uniformTex1 = glGetUniformLocation( shaderProgram, "tex1" );

  //note that the buffers are initialized in the respective constructors
  GLuint texsun = LoadTexture("images/2k_sun.bmp", 2048, 1024);
  // node4 = new csX75::HNode(NULL, curs_ver, v_positions_c, v_colors_earth, v_normals_earth, tex_coords_earth, sizeof(v_positions_earth), sizeof(v_colors_earth), sizeof(v_normals_earth), sizeof(tex_coords_earth), false, tex_earth);
  node4 = new csX75::HNode(NULL, curs_ver, texsun, texsun, v_positions_cursor, v_normals_cursor, v_tex_cursor, sizeof(v_positions_cursor), sizeof(v_normals_cursor), sizeof(v_tex_cursor), false);
  node4->change_parameters(1,1,1,0,0,0);
  load_scn_file();
  
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  glUseProgram(shaderProgram); // to use the grid shader
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
    lookat_matrix = glm::lookAt(glm::vec3(c1_pos), cur_cent, glm::vec3(c1_up));
  }
  else{
    c2_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c2_xrot), glm::vec3(1.0f, 0.0f, 0.0f));
    c2_rotation_matrix = glm::rotate(c2_rotation_matrix, glm::radians(c2_yrot), glm::vec3(0.0f, 1.0f, 0.0f));
    c2_rotation_matrix = glm::rotate(c2_rotation_matrix, glm::radians(c2_zrot), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec4 c2_pos = glm::vec4(c2_xpos, c2_ypos, c2_zpos, 1.0) * c2_rotation_matrix;
    glm::vec4 c2_up = glm::vec4(c2_up_x, c2_up_y, c2_up_z, 1.0) * c2_rotation_matrix;
    //Creating the lookat matrix
    // lookat_matrix = glm::lookAt(glm::vec3(c2_pos), glm::vec3(-0.09,0.22,1.0), glm::vec3(c2_up));
    lookat_matrix = glm::lookAt(glm::vec3(c2_pos), glm::vec3(0.0), glm::vec3(c2_up));
    
  }

  //creating the projection matrix
  if (enable_perspective)
    projection_matrix = glm::frustum(-0.01, 0.01, -0.01, 0.01, 0.01, 15.0);
  //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-3.0, 3.0, -3.0, 3.0, -5.0, 5.0);

  view_matrix = projection_matrix * lookat_matrix;

  // modelview_matrix = view_matrix * model_matrix;
  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // normal_matrix = glm::transpose(glm::inverse(glm::mat3(modelview_matrix)));
  // glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));

  matrixStack.push_back(view_matrix*trans[0]*rot[0]*scale[0]);
  node1e->render_tree();
  matrixStack.pop_back();

  matrixStack.push_back(view_matrix*trans[1]*rot[1]*scale[1]);
  node1->render_tree();
  matrixStack.pop_back();

  matrixStack.push_back(view_matrix*trans[2]*rot[2]*scale[2]);
  node5->render_tree();
  matrixStack.pop_back();

  matrixStack.push_back(view_matrix);
  node4->render_tree();
  matrixStack.pop_back();

  if(sig==1)
  {
    // std::cout<<"ok\n";
    update_bez_curve();
    update_ctrl_pnts(bez_idx);
    std::cout<<"Bezier curve updated\n";
    sig=0;
  }

  if(sig==3)
  {
    update_bez_curve();
    load_all_ctrl_pnts();
    std::cout<<"Bezier curve updated\n";
    sig=0;
  }
  // for(int i=0;i<bez_idx;i++){
  //   for(int j=0;j<3;j++){
  //     std::cout<<bez_ctrl[i][j]<<" ";
  //   }
  //   std::cout<<"\n";
  // }

  if(bez_idx>0)
  {
    matrixStack.push_back(view_matrix);
    node_line->render_tree();
    matrixStack.pop_back();

    matrixStack.push_back(view_matrix);
    bez_node->render_tree();
    matrixStack.pop_back();
  }

  if(animation){
    if(count<5000){
      node2->tx -= 0.01;
      // node2->ty -= 0.01;
      node5->tx -= 0.01;
      // node5->ty -= 0.01;
      node2e->change_rot(-0.5);
      node3e->change_rot(-0.3);
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

// void renderGL(void){
//   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clearing buffer

//   glUseProgram(shaderProgram_cursor); // to use the grid shader
//   glBindVertexArray(vao_cursor);
//   rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
//   rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
//   rotation_matrix = glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));
//   ortho_matrix = glm::ortho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
  
//   // to specify the field of view
//   modelview_matrix = ortho_matrix * rotation_matrix;
//   glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
//   glBindBuffer(GL_ARRAY_BUFFER, vbo_cursor);
//   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(v_positions_cursor), v_positions_cursor);
  
//   glDrawArrays(GL_TRIANGLES, 0, num_vertices_cursor);


// }




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
  glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
  glfwSetCursorPosCallback(window, csX75::cursor_position_callback);

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
