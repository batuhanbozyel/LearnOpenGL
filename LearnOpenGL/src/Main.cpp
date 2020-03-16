//include GLEW before any OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct ShaderProgramSource {
	std::string vertexShader;
	std::string fragmentShader;
	
	std::string& operator[](int index)
	{
		return index == 0 ? vertexShader : fragmentShader;
	}
};

static ShaderProgramSource ParseShader(const std::string& path)
{
	std::ifstream file(path);
	ShaderProgramSource source;
	if (file.is_open())
	{
		enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

		std::string line;
		ShaderType type = ShaderType::NONE;
		while (getline(file, line))
		{
			if (type == ShaderType::NONE)
			{
				if (line.find("#shader vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
					continue;
				}
				else return source;
			}
			else if (type == ShaderType::VERTEX)
			{
				if (line.find("#shader fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
					continue;
				}
			}
			source[(int)type] += line + "\n";
		}
	}
	return source;
}

static int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!\n";
		std::cout << message << "\n";
		glDeleteShader(id);
		delete[] message;
		return 0;
	}
	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	if (!vertexShader.empty() && !fragmentShader.empty())
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
	return 0;
}

int main()
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	// This is where you can start using GLEW
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-0.5f,  0.5f,
		-0.5f, -0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int indices[] = {
		1, 2, 3,
		1, 2, 0
	};

	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	VertexBuffer* vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

	IndexBuffer* ib = new IndexBuffer(indices, 6);

	ShaderProgramSource src = ParseShader("res/shader/Basic.shader");
	unsigned int shader = CreateShader(src.vertexShader, src.fragmentShader);
	if (shader == 0)
	{
		glfwTerminate();
		return -1;
	}
	GLCall(glUseProgram(shader));

	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);
	GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));
	
	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	float r = 0.0f;
	float increment = 0.05f;
	while (!glfwWindowShouldClose(window))
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		GLCall(glUseProgram(shader));
		GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

		GLCall(glBindVertexArray(vao));
		ib->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;
		r += increment;

		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	delete vb;
	delete ib;

	glfwTerminate();

	return 0;
}