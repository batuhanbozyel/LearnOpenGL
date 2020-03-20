//include GLEW before any OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "GLErrors.h"
#include "Renderer.h"
#include "Texture.h"

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
	{
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, // 0
			 0.5f, -0.5f, 1.0f, 0.0f, // 1
			 0.5f,  0.5f, 1.0f, 1.0f, // 2
			-0.5f,  0.5f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		Shader shader("res/shader/Basic.shader");

		Texture texture("res/textures/doge.png");

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();
		texture.Unbind();
		while (!glfwWindowShouldClose(window))
		{
			Renderer::Clear();
			shader.Bind();
			texture.Bind();
			shader.SetUniform1i("u_Texture", 0);
			Renderer::Draw(va, ib, shader);

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}