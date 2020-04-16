#pragma once

#include "Renderer.h"
#include "tests/Test.h"
#include "glm/glm.hpp"

#include <memory>

namespace test
{
	class TestBatchRendering : public Test
	{
	public:
		TestBatchRendering();
		~TestBatchRendering();

		void OnRender() override;
		void OnUpdate(float deltaTime) override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;

		glm::vec3 m_Translation;
	};
}