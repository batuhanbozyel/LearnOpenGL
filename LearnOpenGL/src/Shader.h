#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;

	bool UpdateShaderProgram(const int& index, const std::string& line)
	{
		if (index != -1)
		{
			(*this)[index] += line + "\n";
			return true;
		}
		else return false;
	}

	std::string& operator[](const int& index)
	{
		return index == 0 ? vertexShader : fragmentShader;
	}
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	// Caching for uniforms
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, const glm::vec2& value);
	void SetUniform3f(const std::string& name, const glm::vec3& value);
	void SetUniform4f(const std::string& name, const glm::vec4& value);

	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	ShaderProgramSource ParseShader();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name) const;
};