#include "Rectangle.h"
#include <glad\glad.h>

bool Rectangle::generatedVBOandVAO = false;
unsigned int Rectangle::rectVBO = 0, Rectangle::rectVAO = 0;
Rectangle::Rectangle()
{
	if (!generatedVBOandVAO) {
		float colourRectVertices[] = {
			//positions / colours/ texture coords
	//x  y  z/  r  g   b / Ts   Tt
	0.5, 0.5, 0, 1, 0, 0, 1 , 1,  //top right, index 0
	0.5, -0.5, 0, 0, 1, 0, 1, 0, // bottom right, index 1
	-0.5, -0.5, 0, 0, 0, 1, 0, 0, //bottom left, index 2
	-0.5, 0.5, 0, 1, 1, 0, 0, 1 // top left, index 3
		};
		//order of indexes from above vertices in sets of 3 to describe triangles
		unsigned int rectIndices[] = {
		0,1,3, //first triangle
		1,2,3,//second triangle
		};


		





		unsigned int rectEboID1;

		glGenBuffers(1, &rectEboID1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectEboID1);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectIndices), rectIndices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);  

		//VAO

		glGenVertexArrays(1, &rectVAO);
		glBindVertexArray(rectVAO);

		//VBO
		glGenBuffers(1, &rectVBO);
		glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colourRectVertices), colourRectVertices, GL_STATIC_DRAW);
	
		//EBO
	
		
	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//location = 1, RGB values
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//location = 2, ST texture coordinate values
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//bind rect ebo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectEboID1);

		//unbind VAO
		glBindVertexArray(0);
		

	}
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(glm::mat4& view, glm::mat4& projection)
{
	shader->use();

	glm::mat4 model = glm::mat4(1.0f);


	int modelUniformLocation = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	int viewUniformLocation = glGetUniformLocation(shader->ID, "view");
	glUniformMatrix4fv(viewUniformLocation, 1, GL_FALSE, glm::value_ptr(view));

	int projectionUniformLocation = glGetUniformLocation(shader->ID, "projection");
	glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID1);

	int texture1UniformLocationID = glGetUniformLocation(shader->ID, "texture1");
	glUniform1i(texture1UniformLocationID, 0);

	glActiveTexture(GL_TEXTURE1);


	glBindVertexArray(rectVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
