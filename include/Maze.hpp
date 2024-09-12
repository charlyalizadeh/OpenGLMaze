#ifndef MAZE_H
#define MAZE_H

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


struct Vec2D {
    int x;
    int y;
    Vec2D(): x(0), y(0) {}
    Vec2D(int x, int y): x(x), y(y) {}
};

inline bool operator<(const Vec2D& p1, const Vec2D& p2) {
    if (p1.x != p2.x) {
        return p1.x < p2.x;
    } else {
        return p1.y < p2.y;
    }
};

inline bool operator==(const Vec2D& p1, const Vec2D& p2) {
    return p1.x == p2.x && p1.y == p2.y;
}


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
