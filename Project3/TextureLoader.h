#pragma once
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>


#include "stb_image.h"

using namespace std;

unsigned int loadTexture(const char* fileName, int RGBType);
