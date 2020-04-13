#include "TestSlideBox.h"

#include "imgui/imgui.h"

namespace test
{
	TestSlideBox::TestSlideBox()
		: m_Translation(0, 0, 0), slideSpeed(2.0f), incTranslationX(3.2f), incTranslationY(1.8f), inc(0.03f), directionX(1), directionY(1),
		m_View(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)), 
		m_Proj(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		m_Color[0] = 229.0f/255.0f; m_Color[1] = 245.0f/255.0f; m_Color[2] = 167.0f/255.0f; m_Color[3] = 1.0f;

		float positions[] = {
			   0.0f,   0.0f, 0.0f, 0.0f,
			 200.0f,   0.0f, 1.0f, 0.0f,
			 200.0f, 200.0f, 1.0f, 1.0f,
			   0.0f, 200.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
		
		m_Shader = std::make_unique<Shader>("res/shader/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
	}

	TestSlideBox::~TestSlideBox()
	{

	}

	void TestSlideBox::OnUpdate(float deltaTime)
	{

	}

	void TestSlideBox::OnRender()
	{
		incTranslationX = slideSpeed * 1.6f;
		if (m_Translation.x < 0.0f)
			directionX = 1;
		else if (m_Translation.x > 1720.0f)
			directionX = -1;
		m_Translation.x += incTranslationX * directionX;

		incTranslationY = slideSpeed * 0.9f;
		if (m_Translation.y < 0.0f)
			directionY = 1;
		else if (m_Translation.y > 880.0f)
			directionY = -1;
		m_Translation.y += incTranslationY * directionY;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * model;

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestSlideBox::OnImGuiRender()
	{
		ImGui::SliderFloat("Speed", &slideSpeed, 0.0f, 10.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}