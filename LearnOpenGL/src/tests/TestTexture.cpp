#include "TestTexture.h"

#include "imgui/imgui.h"

namespace test
{
	TestTexture::TestTexture()
		: m_Translation(200, 200, 0), 
		m_Proj(glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
	{
		float positions[] = {
			-100.0f, -100.0f, 0.0f, 0.0f,
			 100.0f, -100.0f, 1.0f, 0.0f,
			 100.0f,  100.0f, 1.0f, 1.0f,
			-100.0f,  100.0f, 0.0f, 1.0f
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

		m_Shader = std::make_unique<Shader>("res/shader/Texture.shader");
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>("res/textures/doge.png");
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	TestTexture::~TestTexture()
	{

	}

	void TestTexture::OnUpdate(float deltaTime)
	{

	}

	void TestTexture::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Texture->Bind();
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);
		Renderer::Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestTexture::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 1920.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}

