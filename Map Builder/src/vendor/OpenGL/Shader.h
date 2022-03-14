#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include "glm/glm.hpp"

class Shader
{
private:
	unsigned int m_Renderer;
	const std::string m_Filepath;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind()  const;
	void Unbind()  const;
	int GetUniformLocation(const std::string& name);
	void Uniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void Uniform1i(const std::string& name, int value);
	void Uniform1f(const std::string& name, float value);
	void UniformMat4f(const std::string& name, const glm::mat4& matrix);
	void Uniform2f(const std::string& name, float v0, float v1);
	
	std::tuple<std::string, std::string> DivideShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

