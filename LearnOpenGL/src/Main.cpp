//include GLEW before any OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "GLErrors.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main()
{
	GLFWwindow* window;
	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);

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
		// 1280 720
		float positions[] = {
			  0.0f,   0.0f, 0.0f, 0.0f, // 0
			100.0f,   0.0f, 1.0f, 0.0f, // 1
			100.0f, 100.0f, 1.0f, 1.0f, // 2
			  0.0f, 100.0f, 0.0f, 1.0f  // 3
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

		// Normalized device coordinates
		glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		// Camera translation
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		// Model translation
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		
		Shader shader("res/shader/Basic.shader");
		shader.Bind();

		Texture texture("res/textures/doge.png");
		texture.Bind();

		// ImGui implementation
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		glm::vec3 translation(0.0f, 0.0f, 0.0f);

		while (!glfwWindowShouldClose(window))
		{
			Renderer::Clear();
			
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			model = glm::translate(glm::mat4(1.0f), translation);
			glm::mat4 mvp = proj * view * model;

			shader.SetUniformMat4f("u_MVP", mvp);
			shader.SetUniform1i("u_Texture", 0);
			
			Renderer::Draw(va, ib, shader);

			{
				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 1280.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}