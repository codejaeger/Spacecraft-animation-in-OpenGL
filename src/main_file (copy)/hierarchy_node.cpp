#include "hierarchy_node.hpp"

#include <iostream>

extern GLuint vPosition,vColor,uModelViewMatrix,vNormal,modelMatrix,normalMatrix,texCoord,shaderProgram,uniformTex0,uniformTex1;
extern std::vector<glm::mat4> matrixStack;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v,GLuint tx1,GLuint tx2, glm::vec4* a_vertices,  glm::vec4* a_normals, glm::vec3* a_tex,std::size_t v_size, std::size_t n_size, std::size_t t_size, bool wire){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		// color_buffer_size = c_size;
		normal_buffer_size = n_size;
		texture_buffer_size = t_size;
		// tex = text;
		tex1 = tx1;
		tex2 = tx2;
		revcl = 0.0;
		// initialize vao and vbo of the object;

		wireframe = wire;

		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		
		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + normal_buffer_size + texture_buffer_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		// glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size , normal_buffer_size, a_normals );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size +  normal_buffer_size, texture_buffer_size, a_tex );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		// glEnableVertexAttribArray( vColor );
		// glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray(vNormal);
  		glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray(texCoord);
  		glVertexAttribPointer(texCoord, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + normal_buffer_size));

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	void HNode::update_matrices(){


		// rev = glm::rotate(glm::mat4(1.0f), glm::radians(revcl), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}


	void HNode::change_rot(GLfloat arc)
	{
		revcl += arc;
		// ry += ary;
		// rz += arz;

		update_matrices();
	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render(){

		//matrixStack multiply
		glUseProgram(shaderProgram);
		glm::mat4* ms_mult = multiply_stack(matrixStack);
		glm::mat4 view = matrixStack[0];
  		glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(view*(*ms_mult)));
		// glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		glUniformMatrix4fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(glm::mat4(*ms_mult)))));
		// glm::mat4 trans = matrixStack[matrixStack.size()-2];
		// glm::mat4 rot = matrixStack[matrixStack.size()-1];
		// matrixStack.pop_back();
		// matrixStack.pop_back();
		// ms_mult = multiply_stack(matrixStack); // view_matrix
		// glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		// matrixStack.push_back(trans);
		// matrixStack.push_back(rot);

		// glBindTexture(GL_TEXTURE_2D, tex);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, tex2 );
		glUniform1i( uniformTex0, 0 ); // Bind the first sampler to texture unit 0.
		glUniform1i( uniformTex1, 1 );
  		glBindVertexArray(vao);
  		// glDrawArrays(GL_TRIANGLE_STRIP, 0, num_vertices);

		// glBindVertexArray (vao);
		if(!wireframe) glDrawArrays(GL_TRIANGLE_STRIP, 0, num_vertices);
		else glDrawArrays(GL_LINE_STRIP, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		// matrixStack.push_back(rev);
		matrixStack.push_back(translation);
		// matrixStack.push_back(rev);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();
		// matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx+=10;
		update_matrices();
	}


	void HNode::inc_ry(){
		ry+=10;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz+=10;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx-=10;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry-=10;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz-=10;
		update_matrices();
	}

	void HNode::dec_x(){
		tx-=0.2;
		update_matrices();
	}

	void HNode::inc_x(){
		tx+=0.2;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=1;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}