#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>


class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void init();
    void setAttribute(unsigned int index, int count,
                      GLenum type, bool normalized,
                      unsigned int stride, const void* pointer) const;
    void bind() const;
    void unbind() const;

private:
    unsigned int m_vertexArrayId;
};


#endif
