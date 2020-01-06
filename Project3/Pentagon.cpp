#include "Pentagon.h"
#include <glad\glad.h>

bool Pentagon::generatedVBOandVAO = false;
unsigned int Pentagon::pentVBO = 0, Pentagon::pentVAO = 0;
Pentagon::Pentagon()
{
	if (!generatedVBOandVAO) {
		float pentVertices[] = {
			-0.3, -0.5, 0,1,0,0,1,1, //top right           index: 0
		-0.5, 0.2,1, 0,1,1,1,0, //bottom right       index: 1
		0.0, 0.5, 0,1,0,1,0,0, //bottom left       index: 2
		0.5, 0.2, 1,1,1,0,0,1,//top left            index: 3
		0.3, -0.5,0,0,1,0,1,0//top left            index: 4
		};

	
	
		//order of indexes from above vertices in sets of 3 to describe triangles
		unsigned int pentIndices[] = {
		0, 1, 2, // first triangle
			  0, 2, 3, // second triangle
			  0, 3, 4  //  third triangle

		};






		//EBO
		unsigned int pentEboID1;

		glGenBuffers(1, &pentEboID1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pentEboID1);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pentIndices), pentIndices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);


	//VAO
		glGenVertexArrays(1, &pentVAO);
		glBindVertexArray(pentVAO);

		//VBO
		glGenBuffers(1, &pentVBO);
		glBindBuffer(GL_ARRAY_BUFFER, pentVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pentVertices), pentVertices, GL_STATIC_DRAW);

		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//location = 1, RGB values
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//location = 2, ST texture coordinate values
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		//bind rect ebo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pentEboID1);

		//unbind VAO
		glBindVertexArray(0);


	}
}

Pentagon::~Pentagon()
{
}

void Pentagon::draw(glm::mat4& view, glm::mat4& projection)
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


	glBindVertexArray(pentVAO);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}
