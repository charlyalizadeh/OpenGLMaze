#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>


class VertexBuffer {
public:
    VertexBuffer();
    VertexBuffer(const void *vertices, unsigned int size);
    ~VertexBuffer();

    void init(const void *vertices, unsigned int size);
    void bind() const;
    void unbind() const;

private:
    unsigned int m_bufferId;
};


#endif
