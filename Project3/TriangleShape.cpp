#include "TriangleShape.h"

TriangleShape::TriangleShape()
{
	float rainbowTriangleVertices[] = {
		//x   y   z    r   g   b
				0.5, -0.5, 0,   1,   0,  0,
				-0.5, -0.5, 0, 0,   1,  0,
				0, 0.5, 0,     0,   0,  1 };
	glGenBuffers(1, &rainbowVboID1);
	glBindBuffer(GL_ARRAY_BUFFER, rainbowVboID1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rainbowTriangleVertices), rainbowTriangleVertices, GL_STATIC_DRAW);
	//VAO
	unsigned int rainbowVaoID1;
	glGenVertexArrays(1, &rainbowVaoID1);
	glBindVertexArray(rainbowVaoID1);
	//LOCATION = 0 is XYZ values
	//note: data is xyzrgb repeated, so stride is now 6, not 3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//enable location 0

	//LOCATION = 1 is RGB values
	//note: RGB values start 3 floats into our buffered array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);//enable location 1

	glBindVertexArray(0);//undind vao
}

TriangleShape::~TriangleShape()
{
}

void TriangleShape::drawTriangle()
{
	Shader shaderProgram5("projectionVertexShader1.txt", "textureFragmentShader2.txt");
	glBindVertexArray(rainbowVaoID1);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}
