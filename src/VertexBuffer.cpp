#include "../include/VertexBuffer.hpp"


VertexBuffer::VertexBuffer(): m_bufferId(0) {}

VertexBuffer::VertexBuffer(const void *vertices, unsigned int size) {
    init(vertices, size);
}

void VertexBuffer::init(const void *vertices, unsigned int size) {
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_bufferId);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_bufferId);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
