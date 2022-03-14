#pragma once
#include "Texture.h"
#include "Shader.h"

class Textures
{
private:
	Shader& m_Shader;
	Texture* coin;
	Texture* brown_brick;
	Texture* pipe;
	Texture* question_mark;
	Texture* mario;
public:
	Textures(Shader& shader);
	~Textures();
	void brown_brick_Render();
	void coin_Render();
	void pipe_Render();
	void question_mark_Render();
	void mario_Render();
	void Unbind();
};

