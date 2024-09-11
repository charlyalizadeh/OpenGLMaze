#ifndef VERTEXINDEXBUFFER_H
#define VERTEXINDEXBUFFER_H

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>


class VertexIndexBuffer {
public:
    VertexIndexBuffer();
    VertexIndexBuffer(const void *indices, unsigned int count);
    ~VertexIndexBuffer();

    void init(const void *indices, unsigned int count);
    void bind() const;
    void unbind() const;

private:
    unsigned int m_bufferId;
};


#endif
