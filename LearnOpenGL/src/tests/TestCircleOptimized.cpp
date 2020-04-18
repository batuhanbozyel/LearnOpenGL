#include "tests/TestCircleOptimized.h"

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "imgui/imgui.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace test
{
	TestCircleOptimized::TestCircleOptimized()
	{
		float halfRadius = 500.0f;
		glm::vec2 center = { 1920.0f / 2, 1080.0f / 2 };
		float positions[] = {
			center.x - halfRadius, center.y - halfRadius, 0.0f, 1.00f, 1.0f, 1.00f, 1.0f,
			center.x + halfRadius, center.y - halfRadius, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
			center.x + halfRadius, center.y + halfRadius, 0.0f, 1.00f, 1.0f, 1.00f, 1.0f,
			center.x - halfRadius, center.y + halfRadius, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0
		};
		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 28 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("res/shader/Circle.shader");
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", glm::mat4(1.0f) * glm::mat4(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)) * glm::mat4(1.0f));
		m_Shader->SetUniform1f("u_halfRadius", halfRadius);
		m_Shader->SetUniform2f("u_resolution", glm::vec2(1920.0f, 1080.0f));
	}

	TestCircleOptimized::~TestCircleOptimized()
	{

	}

	void TestCircleOptimized::OnRender()
	{
		Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestCircleOptimized::OnUpdate(float deltaTime)
	{

	}

	void TestCircleOptimized::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
