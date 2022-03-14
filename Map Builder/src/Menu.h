#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Shader.h"
#include "Textures.h"

class Menu
{
private: 
	char brown_brick = 'B';
	char coin = 'O';
	char pipe = 'U';
	char question_mark = '?';
	char mario = 'X';
	char blank_space = ' ';
	char tileSymbol;
	bool Clear = false;

	bool bind_mario = false;
	bool bind_brown_brick = false;
	bool bind_coin = false;
	bool bind_pipe = false;
	bool bind_question_mark = false;
public:
	Menu();
	~Menu();
	void MenuCheckBox();
	void BindTexture();
	char PassTile();
};

