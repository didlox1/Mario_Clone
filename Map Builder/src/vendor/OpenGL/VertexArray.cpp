#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_Renderer));
}
VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_Renderer));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type , element.normalized, layout.GetStride() * element.count, (const unsigned int*)offset));
		offset += element.count * VertexBufferElements::GetSizeOfType(element.type);
	}
}
void VertexArray::Bind() const {
	glBindVertexArray(m_Renderer);
}
void VertexArray::Unbind() const {
	glBindVertexArray(0);
}