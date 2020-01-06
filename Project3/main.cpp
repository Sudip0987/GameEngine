#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Shader.h"

#include <glm/glm.hpp> //basic glm funcs/types
#include <glm/gtc/matrix_transform.hpp> //glm matrix functions/types
#include <glm/gtc/type_ptr.hpp>//converts glm types to opengl types

#define STB_IMAGE_IMPLEMENTATION
#include "TextureLoader.h"

#include "Rectangle.h"
#include "Pentagon.h"
using namespace std;


//indicates current shape to be drawn
int currentShapeToDraw = 1;

//window resize callback function
void windowResizeCallBack(GLFWwindow* window, int width, int height);

//process user inputs
void processInputs(GLFWwindow* window);


//VERTEX SHADER PROGRAM SOURCE CODE
//pass data into gl_Position
const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

//FRAGMENT SHADER
//pass a vec4 to the next shader representing a final colour for a pixel
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"//out variables are passed to the next shader
"\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

bool checkShaderCompileErrors(int shaderID) {
	int success;//failed or not
	char infoLog[512]; //store error info
	//check compile status
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	//report if it failed
	if (!success)
	{
		//get error and display it
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		cout << "Shader compile error!!! " << infoLog << endl;
		system("pause");

		return false;
	}

	return true;

}

bool checkShaderLinkingErrors(int shaderProgramID) {
	int success;
	char infoLog[512];
	//check if successful
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		cout << "Shader Linking Error: " << infoLog << endl;
		system("pause");
		return false;
	}

	return true;
}

void main() {
	//setup a window to use for opengl renderering
	glfwInit();
	//user 3.3 core profile opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //the first 3 in 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //the .3 in 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //core profile

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Assignment1", NULL, NULL);
	//did it fail?
	if (window == NULL) {
		cout << "Window error! " << endl;
		glfwTerminate();
		system("pause");
		return; //exit program early
	}

	//make this window the main window
	glfwMakeContextCurrent(window);

	//use glad to bind functions from gpu drivers to our opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//it failed!
		cout << "GLAD failed!" << endl;
		glfwTerminate();
		system("pause");
		return;
	}
	//tell openGL which part of our window it can render to
	glViewport(0, 0, 1280, 720);//x,y,w,h

	//turn on z buffering
	glEnable(GL_DEPTH_TEST);

	//set it so when the screen changes size, our function is called for this window
	glfwSetFramebufferSizeCallback(window, windowResizeCallBack);

	//tell stbi to flip images loaded in
	stbi_set_flip_vertically_on_load(true);



	//Accessing the shader files

	Shader shaderProgram5("projectionVertexShader1.txt", "textureFragmentShader2.txt");
	Shader shaderProgram6("projectionVertexShader1.txt", "textureFragmentShader3.txt");




	//Load Texture
	unsigned int textureID1 = loadTexture("paper.png", GL_RGB);
	unsigned int textureID2 = loadTexture("blackT.PNG", GL_RGB);


	//Rectangle
	Rectangle rectangle;
	rectangle.shader = &shaderProgram6;
	rectangle.textureID1 = textureID1;

	//Triangle
	float triangleVertices[] = {
		//x   y   z    r   g   b
		0.5, -0.5, 0,   1,   0,  0,
		-0.5, -0.5, 0, 0,   1,  0,
		0, 0.5, 0,     0,   0,  1
	};
	//VBO
	unsigned int triangleVBO;
	glGenBuffers(1, &triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
	//VAO
	unsigned int triangleVAO;
	glGenVertexArrays(1, &triangleVAO);
	glBindVertexArray(triangleVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);//enable location 0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);//enable location 1
	glBindVertexArray(0);



	//Pentagon
	Pentagon pentagon;
	pentagon.shader = &shaderProgram5;
	pentagon.textureID1 = textureID2;

	

	//SETUP CAMERA
	glm::mat4 view = glm::mat4(1.0f);

	glm::mat4 projection = glm::mat4(1.0f);

	//GAME LOOP
	while (!glfwWindowShouldClose(window)) {
		//user inputs
		processInputs(window);

		//RENDERING
		//set clear colour
		glClearColor(0, 0, 1, 1); //rgba, values 0-1 e.g 0.67
		//clear screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw Triangle
		if (currentShapeToDraw == 1) {
			pentagon.draw(view, projection);
			
		}
		//Draw Rectangle
		if (currentShapeToDraw == 2) {
			rectangle.draw(view, projection);

		}
		//Draw
		if (currentShapeToDraw == 3) {
			shaderProgram5.use();
			glBindVertexArray(triangleVAO);

			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	
		//process any polled events
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	system("pause");
}


	



void windowResizeCallBack(GLFWwindow* window, int width, int height) {
	//resize opengl viewport
	glViewport(0, 0, width, height);
}

void processInputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		currentShapeToDraw = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		currentShapeToDraw = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		currentShapeToDraw = 3;
	}

}
