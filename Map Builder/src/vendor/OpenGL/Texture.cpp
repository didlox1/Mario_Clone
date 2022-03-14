#include "Texture.h"

Texture::Texture(const std::string& filepath)
	:m_Renderer(0), m_Filepath(filepath), m_Height(0), m_Width(0),
	m_BPP(0), m_Localbuffer(nullptr)
{
	GLCall(glGenTextures(1, &m_Renderer));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Renderer));

	stbi_set_flip_vertically_on_load(1);
	m_Localbuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Localbuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	if (m_Localbuffer)
		stbi_image_free(m_Localbuffer);
}
Texture::~Texture() {
	GLCall(glDeleteTextures(1, &m_Renderer));
}

void Texture::Bind(unsigned int slot){
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_Renderer));
}
void Texture::Unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}