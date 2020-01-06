#pragma once
#include "Shader.h"
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> //basic glm funcs/types
#include <glm/gtc/matrix_transform.hpp> //glm matrix functions/types
#include <glm/gtc/type_ptr.hpp>//converts glm types to opengl types
class Rectangle
{
public:
	Shader* shader;
	unsigned int textureID1;

	//xyz of where this Rectangle is in the world
	glm::vec3 pos;

	static bool generatedVBOandVAO;
	static unsigned int rectVBO, rectVAO;

	Rectangle();
	~Rectangle();

	void draw(glm::mat4& view, glm::mat4& projection);
};

