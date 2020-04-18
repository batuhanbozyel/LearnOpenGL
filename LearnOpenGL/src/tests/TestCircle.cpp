#include "tests/TestCircle.h"

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include "imgui/imgui.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace test
{
	TestCircle::TestCircle()
	{
		const int triangles = 1000;
		const float halfRadius = 500.0f;
		glm::vec2 center = { 1920.0f / 2, 1080.0f / 2 };
		glm::vec2 positions[triangles];
		for (int i = 0; i < triangles; i++)
		{
			float angle = (i / (float)triangles) * 2 * M_PI;
			positions[i].x = center.x + halfRadius * cos(angle);
			positions[i].y = center.y + halfRadius * sin(angle);
		}

		float vertices[7 * (triangles + 1)];
		unsigned int indices[3 * triangles];
		vertices[0] = 1920.0f / 2;
		vertices[1] = 1080.0f / 2;
		vertices[2] = 0.0f;

		vertices[3] = 0.18f;
		vertices[4] = 0.6f;
		vertices[5] = 0.96f;
		vertices[6] = 1.0f;
		int offset = 7;
		for (int i = 1; i <= triangles; i++)
		{
			vertices[i * offset] = positions[i - 1].x;
			vertices[i * offset + 1] = positions[i - 1].y;
			vertices[i * offset + 2] = 0.0f;

			if (i % 2 == 0)
			{
				vertices[i * offset + 3] = 0.18f;
				vertices[i * offset + 4] = 0.6f;
				vertices[i * offset + 5] = 0.96f;
				vertices[i * offset + 6] = 1.0f;
			}
			else
			{
				vertices[i * offset + 3] = 1.0f;
				vertices[i * offset + 4] = 1.0f;
				vertices[i * offset + 5] = 1.0f;
				vertices[i * offset + 6] = 1.0f;
			}


			indices[3 * (i - 1)] = 0;
			indices[3 * (i - 1) + 1] = i;
			if (i != triangles) indices[3 * (i - 1) + 2] = i + 1;
			else indices[3 * (i - 1) + 2] = 1;
		}

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 7 * (triangles + 1) * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 3 * triangles);

		m_Shader = std::make_unique<Shader>("res/shader/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", glm::mat4(1.0f) * glm::mat4(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)) * glm::mat4(1.0f));
	}

	TestCircle::~TestCircle()
	{

	}

	void TestCircle::OnRender()
	{
		Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestCircle::OnUpdate(float deltaTime)
	{

	}

	void TestCircle::OnImGuiRender()
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
