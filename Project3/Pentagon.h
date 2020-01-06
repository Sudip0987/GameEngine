#pragma once
#include "Shader.h"
#include <GLFW\glfw3.h>
#include <glm/glm.hpp> //basic glm funcs/types
#include <glm/gtc/matrix_transform.hpp> //glm matrix functions/types
#include <glm/gtc/type_ptr.hpp>//converts glm types to opengl types
class Pentagon
{
public:
	Shader* shader;
	unsigned int textureID1;

	glm::vec3 pos;

	static bool generatedVBOandVAO;
	static unsigned int pentVBO, pentVAO;

	Pentagon();
	~Pentagon();

	void draw(glm::mat4& view, glm::mat4& projection);
};

