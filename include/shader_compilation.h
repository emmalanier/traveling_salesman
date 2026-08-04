//Shaders for OpenGL//

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

GLuint load_shader(const char*, const char*);

#endif //SHADER_H