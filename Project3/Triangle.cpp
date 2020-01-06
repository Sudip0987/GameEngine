
#include "Triangle.h"
#include <glad\glad.h>

bool Triangle::generatedVBOandVAO = false;
unsigned int Triangle::triangleVBO = 0, Triangle::triangleVAO = 0;

Triangle::Triangle()
{
	if (!generatedVBOandVAO) {
		float triangleVertices[] = {
			//x   y   z    r   g   b
					0.5, -0.5, 0,   1,   0,  0,
					-0.5, -0.5, 0, 0,   1,  0,
					0, 0.5, 0,     0,   0,  1 };


		

		glGenBuffers(1, &triangleVBO);
		glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

		glGenVertexArrays(1, &triangleVAO);
		glBindVertexArray(triangleVAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//note: RGB values start 3 floats into our buffered array
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);//enable location 1

		//unbind VAO
		glBindVertexArray(0);

	}
	
}

Triangle::~Triangle()
{
}

void Triangle::draw(glm::mat4& view, glm::mat4& projection)
{

	shader->use();

	glm::mat4 triangleModel = glm::mat4(1.0f);

	int modelUniformLocation = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(triangleModel));

	int viewUniformLocation = glGetUniformLocation(shader->ID, "view");
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	int projectionUniformLocation = glGetUniformLocation(shader->ID, "projection");
	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

	//tell our fragment shader to look in texture slot 0 for our crate texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID1);
	int texture1UniformLocationID = glGetUniformLocation(shader->ID, "texture1");
	glUniform1i(texture1UniformLocationID, 0); //ie - set texture1 variable on frag shader to value 0

	glActiveTexture(GL_TEXTURE1);

	glBindVertexArray(triangleVAO);
	//draw the vertex array
	//params: primitive type(triangles, points, line_strips)
	//		starting index in array
	//		how many vertexes to draw from vbo
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


