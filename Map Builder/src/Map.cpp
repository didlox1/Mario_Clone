#include "Map.h"

Map::Map(std::string filepath, Shader& shader, VertexArray& va, IndexBuffer& ib, Menu& menu)
	:m_Filepath(filepath), m_Shader(shader), m_IndexBuffer(ib), m_VertexArray(va), m_Menu(menu)
{
	m_MouseCoord = glm::vec2(0.0f, 0.0f);
	for (int y = 0; y < HEIGHT / QUAD_SIZE; y++) {
		for (int x = 0; x < WIDTH / QUAD_SIZE; x++) {
			mapElements[y][x] = blank_space;
		}
	}
	m_Shader.Bind();
	projection = glm::ortho(0.0f,(float)WIDTH, 0.0f,(float)HEIGHT, -1.0f, 1.0f);
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


void Map::SaveToString() {
	if (m_ClickState) {
		system("cls");
		for (int y = 0; y < HEIGHT/QUAD_SIZE ; y++) {
			for (int x = 0; x < WIDTH/QUAD_SIZE; x++) {
				if (floor(m_MouseCoord.x/QUAD_SIZE) == x && floor(m_MouseCoord.y / QUAD_SIZE) == y) {
					m_Menu.BindTexture();
					mapElements[y][x] = m_Menu.PassTile(); 
				}
				if(mapElements[y][x] == blank_space) {
					mapElements[y][x] = blank_space;
				}
			}
		}
	}
	ChangeClickState();
}

void Map::DrawMapElements(){
	for (int y = 0; y < HEIGHT / QUAD_SIZE; y++) {
		for (int x = 0; x < WIDTH / QUAD_SIZE; x++) {
			if (mapElements[y][x] != blank_space) {
				BindTexture(x, y);
				modelCoord = glm::vec3(x * QUAD_SIZE,HEIGHT-(y*QUAD_SIZE)-QUAD_SIZE, 0.0f);
				model = glm::translate(glm::mat4(1.0f), modelCoord);
				MVP = projection * model;
				m_Shader.UniformMat4f("u_MVP", MVP);
				renderer->Draw(m_VertexArray, m_IndexBuffer, m_Shader);
			}
		}
	}
}

void Map::BindTexture(int& x, int& y) {
	if (mapElements[y][x] == brown_brick) {
		tex->brown_brick_Render();
	}
	if (mapElements[y][x] == coin) {
		tex->coin_Render();
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
	if (mapElements[y][x] == mario) {
		tex->mario_Render();
	}
}

void Map::WindowClear() {
	if (ImGui::Button("Clear Window")) {
		for (int y = 0; y < HEIGHT / QUAD_SIZE; y++) {
			for (int x = 0; x < WIDTH / QUAD_SIZE; x++) {
				mapElements[y][x] = blank_space;
			}
		}
	}
}

void Map::MapSave() {
	if (ImGui::Button("Save Map")) {
		std::ofstream wfile;
		wfile.open(m_Filepath.c_str());
		for (int y = 0; y < HEIGHT / QUAD_SIZE; y++){
			for (int x = 0; x < WIDTH / QUAD_SIZE; x++) {
				wfile << mapElements[y][x];
			}
			wfile << std::endl;
		}
		wfile.close();
	}
}