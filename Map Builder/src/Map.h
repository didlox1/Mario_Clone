#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <array>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "Renderer.h"
#include "Textures.h"
#include "Menu.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define QUAD_SIZE 30
#define MAP_LENGTH 120
#define WIDTH 960
#define HEIGHT 540

class Map
{
private:
	char brown_brick = 'B';
	char coin = 'O';
	char pipe = 'U';
	char question_mark = '?';
	char mario = 'X';
	char blank_space = ' ';
	char tile = ' ';

	bool m_ClickState = false;
	glm::vec2 m_MouseCoord;
	std::string m_Filepath;
	std::array<char[WIDTH/QUAD_SIZE], (HEIGHT / QUAD_SIZE)> mapElements; //error here
	
	Renderer* renderer;
	Shader& m_Shader;
	VertexArray& m_VertexArray;
	IndexBuffer& m_IndexBuffer;
	Menu& m_Menu;
	Textures* tex;

	glm::mat4 projection;
	glm::vec3 modelCoord;
	glm::mat4 model;
	glm::mat4 MVP;

public:
	Map(std::string filepath, Shader& shader, VertexArray& va, IndexBuffer& ib, Menu& menu);
	~Map();
	void MapSave();
	void SaveToString();
	void DrawMapElements();
	void BindTexture(int& x, int& y);
	inline void PassMouseCoord(glm::vec2 coord) { m_MouseCoord = coord; };
	inline void ChangeClickState() { m_ClickState = !m_ClickState; };
	void WindowClear();
};

