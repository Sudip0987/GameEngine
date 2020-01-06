#pragma once
#pragma once
#include "Shader.h"
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> //basic glm funcs/types
#include <glm/gtc/matrix_transform.hpp> //glm matrix functions/types
#include <glm/gtc/type_ptr.hpp>//converts glm types to opengl types
class TriangleShape
{
public:
	unsigned int rainbowVboID1;
	unsigned int rainbowVaoID1;

	TriangleShape();
	~TriangleShape();

	void drawTriangle();

};

