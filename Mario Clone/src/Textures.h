#pragma once
#include "Texture.h"
#include "Shader.h"

class Textures
{
private:
	Shader& m_Shader;
	Texture* coin[8];
	Texture* brown_brick;
	Texture* pipe;
	Texture* question_mark;
	Texture* mario[2];
	Texture* mario_jumping[2];
public:
	Textures(Shader& shader);
	~Textures();
	void brown_brick_Render();
	void coin_Render(int x);
	void pipe_Render();
	void question_mark_Render();
	void mario_Render();
	void mario_Walk();
	void mario_Jump(int x);
	void Unbind();
};

