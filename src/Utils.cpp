#include "../include/Maze.hpp"


void clearError() {
    while(glGetError());
}

void checkError() {
    while(GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}

template<class T>
void coutVector(std::vector<T> v, int newLineIndex)
{
    for(size_t i = 0; i < v.size(); i++)
    {
        if(newLineIndex != -1 && i % newLineIndex == 0)
            std::cout << "\n";
        std::cout << v[i] << ",";
    }
    std::cout << "\n";
}
