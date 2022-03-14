#include "Textures.h"

Textures::Textures(Shader& shader)
	:m_Shader(shader)
{
	m_Shader.Uniform1i("tex", 0);
	coin[0] = new Texture("res/Textures/coin_1.png");
	coin[1] = new Texture("res/Textures/coin_2.png");
	coin[2] = new Texture("res/Textures/coin_3.png");
	coin[3] = new Texture("res/Textures/coin_4.png");
	brown_brick = new Texture("res/Textures/brown_brick.png");
	pipe = new Texture("res/Textures/pipe.png");
	question_mark = new Texture("res/Textures/question_mark.png");
	mario[0] = new Texture("res/Textures/mario/mario_walk_1.png");
	mario[1] = new Texture("res/Textures/mario/mario_walk_2.png");
	mario_jumping[0] = new Texture("res/Textures/mario/mario_jumping_1.png");
	mario_jumping[1] = new Texture("res/Textures/mario/mario_falling_1.png");
}

Textures::~Textures() {
	delete brown_brick;
	delete coin;
	delete pipe;
	delete question_mark;
	delete mario;
	delete mario_jumping;
}

void Textures::brown_brick_Render() {
	brown_brick->Bind();
}

void Textures::coin_Render(int x) {
	coin[x]->Bind();
}

void Textures::pipe_Render() {
	pipe->Bind();
}

void Textures::question_mark_Render() {
	question_mark->Bind();
}

void Textures::mario_Render() {
	mario[0]->Bind();
}

void Textures::mario_Walk() {
	mario[1]->Bind();
}

void Textures::mario_Jump(int x) {
	mario_jumping[x]->Bind();
}

void Textures::Unbind() {
	brown_brick->Unbind();
	pipe->Unbind();
	question_mark->Unbind();
	for (int x = 0; x < (sizeof(coin) / sizeof(coin[0])); x++) {
		coin[x]->Unbind();
	}
	for (int x = 0; x < (sizeof(mario) / sizeof(mario[0])); x++) {
		mario[x]->Unbind();
	}
	for (int x = 0; x < (sizeof(mario_jumping) / sizeof(mario_jumping[0])); x++) {
		mario_jumping[x]->Unbind();
	}
}