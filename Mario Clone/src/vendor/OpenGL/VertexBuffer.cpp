#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(unsigned int size, const void* data) {
    GLCall(glGenBuffers(1, &m_Renderer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_Renderer));
}

void VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer));
}
void VertexBuffer::Unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}


