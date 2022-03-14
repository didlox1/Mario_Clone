#include "Textures.h"

Textures::Textures(Shader& shader)
	:m_Shader(shader)
{
	m_Shader.Uniform1i("tex", 0);
	coin = new Texture("res/Textures/coin.png");
	brown_brick = new Texture("res/Textures/brown_brick.png");
	pipe = new Texture("res/Textures/pipe.png");
	question_mark = new Texture("res/Textures/question_mark.png");
	mario = new Texture("res/Textures/mario_walk_1.png");
}

Textures::~Textures() {
	delete brown_brick;
	delete coin;
	delete pipe;
	delete question_mark;
	delete mario;
}

void Textures::brown_brick_Render() {
	brown_brick->Bind();
}

void Textures::coin_Render() {
	coin->Bind();
}

void Textures::pipe_Render() {
	pipe->Bind();
}

void Textures::question_mark_Render() {
	question_mark->Bind();
}

void Textures::mario_Render() {
	mario->Bind();
}

void Textures::Unbind() {
	brown_brick->Unbind();
	coin->Unbind();
	pipe->Unbind();
	question_mark->Unbind();
	mario->Unbind();
}