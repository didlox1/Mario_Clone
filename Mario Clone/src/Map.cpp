#include "Map.h"

Map::Map(std::string filepath, Shader& shader, VertexArray& va, IndexBuffer& ib)
	:m_Filepath(filepath), m_Shader(shader), m_IndexBuffer(ib), m_VertexArray(va)
{
	ReadFromString();
	m_Shader.Bind();
	projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);
	modelCoord = glm::vec3(0.0f, 0.0f, 0.0f);
	model = glm::translate(glm::mat4(1.0f), modelCoord);
	MVP = projection * model;
	m_Shader.UniformMat4f("u_MVP", MVP);
	tex = new Textures(m_Shader);
	renderer = new Renderer;
}

Map::~Map() {
	delete tex;
	delete renderer;
}

void Map::OnRender()
{
	if(moveRight) {
		m_Shader.Uniform1i("faceing", 1);
		MoveRight();
	}
	if(moveLeft) {
		m_Shader.Uniform1i("faceing", 0);
		MoveLeft();
	}
	Jump();
	DrawMapElements();
	tex->mario_Render();
	std::cout << MoneyCounter << std::endl;
}


void Map::ReadFromString() {
	line_nr = 0;
	rfile.open(m_Filepath.c_str());
	while(std::getline(rfile, line)){
		for (int x = 0; x < line.size(); x++) {
			mapElements[line_nr][x] = line[x];
			if (mapElements[line_nr][x] == mario) {
				MarioLocation = glm::vec2(x, line_nr);
				mapElements[line_nr][x] = blank_space;
			}
		}
		line_nr++;
	}
}

void Map::DrawMapElements() {
	//Draw Mario
	DrawMario();
	m_Shader.Uniform1i("faceing", 1);
	//Draw Obstacles
	for (int y = 0; y < HEIGHT / QUAD_SIZE; y++) {
		for (int x = 0; x < WIDTH / QUAD_SIZE; x++) {
			if (mapElements[y][x] != blank_space && mapElements[y][x] != mario) {
				BindTexture(x, y);
				modelCoord = glm::vec3(x * QUAD_SIZE, HEIGHT - (y * QUAD_SIZE) - QUAD_SIZE, 0.0f);
				model = glm::translate(glm::mat4(1.0f), modelCoord);
				MVP = projection * model;
				m_Shader.UniformMat4f("u_MVP", MVP);
				renderer->Draw(m_VertexArray, m_IndexBuffer, m_Shader);
				tex->Unbind();
			}
		}
	}
	currentCoinShape++;

}

void Map::DrawMario()
{
	modelCoord = glm::vec3(MarioLocation.x * QUAD_SIZE, HEIGHT - (MarioLocation.y * QUAD_SIZE + QUAD_SIZE), 0.0f);
	model = glm::translate(glm::mat4(1.0f), modelCoord);
	MVP = projection * model;
	m_Shader.UniformMat4f("u_MVP", MVP);
	renderer->Draw(m_VertexArray, m_IndexBuffer, m_Shader);
	tex->Unbind();
}

void Map::ChangeMarioSprite() {
	if(currentShape == 0) {
		tex->mario_Render();
	}
	if (currentShape == 1) {
		tex->mario_Walk();
	}
	if (currentShape < 2) {
		currentShape++;
	}
	else if (currentShape >= 2) {
		currentShape = 0;
	}
}

void Map::ChangeCoinSprite() {
	if (currentCoinShape < 12) {
		tex->coin_Render(ceil(currentCoinShape / 3));
	}
	if (currentCoinShape >= 12) {
		currentCoinShape = 0;
		tex->coin_Render(0);
	}
}

void Map::BindTexture(int& x, int& y) {
	if (mapElements[y][x] == brown_brick) {
		tex->brown_brick_Render();
	}
	if (mapElements[y][x] == coin) {
		ChangeCoinSprite();
	}
	if (mapElements[y][x] == pipe) {
		tex->pipe_Render();
	}
	if (mapElements[y][x] == question_mark) {
		tex->question_mark_Render();
	}
	if (mapElements[y][x] == blank_space) {
		tex->Unbind();
	}
}

////////////////////////////////////////// Movement ///////////////////////////////////////////// 


void Map::MoveRight() {
	if (CheckForCollision(right)) {
		ChangeMarioSprite();
		MarioLocation.x += 0.25;
	}
}

void Map::MoveLeft() {
	if (CheckForCollision(left)) {
		ChangeMarioSprite();
		MarioLocation.x -= 0.25;
	}
}

int Map::Jump() {
	if (whileJumping) {
		canJump = false;
		if (!isFalling) {
			if (CheckForCollision(up)) {
				tex->mario_Jump(0);
				if (MarioLocation.y >= MarioStandingHeight - JUMP_HEIGHT) {
					MarioLocation.y -= 0.5f;
					return true;
				}
			}
		}
		isFalling = true;
	}
	if (CheckForCollision(down)) {
		MarioLocation.y += 0.5f;
		tex->mario_Jump(1);
		return true;
	}
	canJump = true;
	whileJumping = false;
	return true;
}

bool Map::CheckForCollision(float direction)
{
	if (direction == up || direction == down) {
		if ((floor(MarioLocation.y) + direction) >= 0) {
			if (mapElements[floor(MarioLocation.y) + direction][int(floor(MarioLocation.x))] == blank_space && mapElements[floor(MarioLocation.y) + direction][int(ceil(MarioLocation.x))] == blank_space) {
				return true;
			}
			if (mapElements[floor(MarioLocation.y) + direction][int(floor(MarioLocation.x))] == coin || mapElements[floor(MarioLocation.y) + direction][int(ceil(MarioLocation.x))] == coin) {
				if (mapElements[floor(MarioLocation.y) + direction][int(floor(MarioLocation.x))] == coin && mapElements[floor(MarioLocation.y) + direction][int(ceil(MarioLocation.x))] == coin) //error
				{
					MoneyCounter += 2;
					mapElements[floor(MarioLocation.y) + direction][int(floor(MarioLocation.x))] = blank_space;
					mapElements[floor(MarioLocation.y) + direction][int(ceil(MarioLocation.x))] = blank_space;
					return true;
				}
				else {
					MoneyCounter++;
					mapElements[floor(MarioLocation.y) + direction][int(floor(MarioLocation.x))] = blank_space;
					mapElements[floor(MarioLocation.y) + direction][int(ceil(MarioLocation.x))] = blank_space;
					return true;
				}
			}
		}
	}
	if (direction == up) {
		if (mapElements[floor(MarioLocation.y) + direction][int(floor(MarioLocation.x))] == question_mark || mapElements[floor(MarioLocation.y) + direction][int(ceil(MarioLocation.x))] == question_mark) {
			if (mapElements[floor(MarioLocation.y) + direction][int(floor(MarioLocation.x))] == question_mark) {
				mapElements[floor(MarioLocation.y) + direction][int(floor(MarioLocation.x))] = blank_space;
			}
			else {
				mapElements[floor(MarioLocation.y) + direction][int(ceil(MarioLocation.x))] = blank_space;
			}
			MoneyCounter += 3;
			return false;
		}
	}
	if (direction == left) {
		if (mapElements[ceil(MarioLocation.y)][int(floor(MarioLocation.x + direction))] == blank_space) {
			return true;
		}
		if (mapElements[ceil(MarioLocation.y)][int(floor(MarioLocation.x + direction))] == coin) {
			MoneyCounter++;
			mapElements[ceil(MarioLocation.y)][int(floor(MarioLocation.x + direction))] = blank_space;
			return true;
		}
	}
	if (direction == right) {
		if (mapElements[ceil(MarioLocation.y)][int(ceil(MarioLocation.x + direction))] == blank_space) {
			return true;
		}
		if (mapElements[ceil(MarioLocation.y)][int(ceil(MarioLocation.x + direction))] == coin) {
			MoneyCounter++;
			mapElements[ceil(MarioLocation.y)][int(ceil(MarioLocation.x + direction))] = blank_space;
			return true;
		}
	}
	return false;
}

void Map::CheckStandingLocation()
{
	MarioStandingHeight = MarioLocation.y;
}


