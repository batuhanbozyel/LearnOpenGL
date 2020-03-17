#pragma once

#include <string>
#include <unordered_map>

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
	// caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	ShaderProgramSource ParseShader();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};