#pragma once
#include "Renderer.h"
#include "vendor\stb\stb_image.h"

class Texture
{
private:
	unsigned int m_Renderer;
	std::string m_Filepath;
	unsigned char* m_Localbuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(unsigned int slot = 0);
	void Unbind() const;

	inline const int GetWidth() { return m_Width; };
	inline const int GetHeight() { return m_Height; };
};

