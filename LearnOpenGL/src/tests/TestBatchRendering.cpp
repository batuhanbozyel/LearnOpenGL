#include "TestBatchRendering.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

namespace test
{
	TestBatchRendering::TestBatchRendering()
		: m_View(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)),
		m_Proj(1.0f), m_Model(1.0f), m_Translation(0, 0, 0)
	{
		float positions[] = {
			200.0f, 200.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
			400.0f, 200.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
			400.0f, 400.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,
			200.0f, 400.0f, 0.0f, 0.18f, 0.6f, 0.96f, 1.0f,

			600.0f, 200.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f,
			800.0f, 200.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f,
			800.0f, 400.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f,
			600.0f, 400.0f, 0.0f, 1.0f, 0.93f, 0.24f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4
		};

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 7 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 12);

		m_Shader = std::make_unique<Shader>("res/shader/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * m_Model);
	}

	TestBatchRendering::~TestBatchRendering()
	{
		
	}

	void TestBatchRendering::OnRender()
	{
		m_Model = glm::translate(glm::mat4(1.0f), m_Translation);
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * m_Model);
		Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestBatchRendering::OnUpdate(float deltaTime)
	{

	}

	void TestBatchRendering::OnImGuiRender()
	{
		ImGui::SliderFloat3("model", &m_Translation.x, 0.0f, 1000.0f);
	}

}