#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(unsigned int count, const unsigned int* data)
	:m_Count(count)
{
	GLCall(glGenBuffers(1, &m_Renderer));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_Renderer));
}

void IndexBuffer::Bind()  const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer));
}
void IndexBuffer::Unbind()  const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
