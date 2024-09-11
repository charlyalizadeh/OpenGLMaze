#ifndef MAZE_H
#define MAZE_H

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


void checkError();
void clearError();
template<class T>
void coutVector(std::vector<T> v, int newLineIndex = -1);

void initGLFW(int minor = 3, int major = 3);
GLFWwindow* createWindow(int width, int height);
void framebufferSizCallback(GLFWwindow* window, int width, int height);
GLFWwindow* initOpenGL(int width, int height, int minor = 3, int major = 3);

void processInput(GLFWwindow *window);


#endif
