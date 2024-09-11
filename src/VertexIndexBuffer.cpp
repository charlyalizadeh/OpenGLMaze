#include "../include/VertexIndexBuffer.hpp"


VertexIndexBuffer::VertexIndexBuffer(): m_bufferId(0) {}

VertexIndexBuffer::VertexIndexBuffer(const void *indices, unsigned int count) {
    init(indices, count);
}

void VertexIndexBuffer::init(const void *indices, unsigned int count) {
    glGenBuffers(1, &m_bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

VertexIndexBuffer::~VertexIndexBuffer() {
    glDeleteBuffers(1, &m_bufferId);
}

void VertexIndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferId);
}

void VertexIndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
