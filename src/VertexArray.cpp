#include "../include/VertexArray.hpp"


VertexArray::VertexArray() {
    init();
}

void VertexArray::init() {
    int currentBufferId;
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentBufferId);
    if(currentBufferId == 0)
        return;

    glGenVertexArrays(1, &m_vertexArrayId);
    glBindVertexArray(m_vertexArrayId);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_vertexArrayId);
}

void VertexArray::setAttribute(unsigned int index, int count,
                               GLenum type, bool normalized,
                               unsigned int stride, const void* pointer) const {
    glVertexAttribPointer(index, count, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void VertexArray::bind() const {
    glBindVertexArray(m_vertexArrayId);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
