#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <array>
#include <vector>
#include <windows.h>

#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "Renderer.h"
#include "Textures.h"

#define QUAD_SIZE 30
#define MAP_LENGTH 120
#define WIDTH 960
#define HEIGHT 540
#define WIDTH_IN_QUADS 32
#define HEIGHT_IN_QUADS 18
#define QUAD_MOVE_SIZE 10
#define MOVE_LENGTH 1
#define JUMP_HEIGHT 2

class Map
{
private:
	float left = -0.25;
	float right = 0.25;
	float up = -1.0;
	float down = 1.0;

	char brown_brick = 'B';
	char coin = 'O';
	char pipe = 'U';
	char question_mark = '?';
	char mario = 'X';
	char blank_space = ' ';

	char tile;
	Renderer* renderer;
	glm::vec2 m_MouseCoord;
	std::string m_Filepath;
	Shader& m_Shader;
	VertexArray& m_VertexArray;
	IndexBuffer& m_IndexBuffer;
	Textures* tex;
	std::string line;
	std::ifstream rfile;
	int line_nr = 1;
	int MarioStandingHeight;
	int MoneyCounter = 0;
	bool isJumping = false;
	int currentShape = 0;
	int currentCoinShape = 0;

	std::array<char[WIDTH / QUAD_SIZE], (HEIGHT / QUAD_SIZE)> mapElements;
	std::vector<glm::vec2> brickLocation;
	std::vector<glm::vec2> pipeLocation;
	std::vector<glm::vec2> coinLocation;
	glm::vec2 MarioLocation;

	glm::mat4 projection;
	glm::vec3 modelCoord;
	glm::mat4 model;
	glm::mat4 MVP;

public:
	Map(std::string filepath, Shader& shader, VertexArray& va, IndexBuffer& ib);
	~Map();
	void OnRender();
	//Draw Functions
	void ReadFromString();
	void ChangeMarioSprite();
	void DrawMapElements();
	void DrawMario();
	void BindTexture(int& x, int& y);
	void ChangeCoinSprite();
	//Movement
	void MoveRight();
	void MoveLeft();
	int Jump();
	void CheckStandingLocation();
	bool CheckForCollision(float direction);
	bool whileJumping = false;
	bool isFalling = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool canJump = true;
};

