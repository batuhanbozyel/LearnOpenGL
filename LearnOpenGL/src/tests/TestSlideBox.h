#pragma once

#include <memory>

#include "Test.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
	class TestSlideBox : public Test
	{
	public:
		TestSlideBox();
		~TestSlideBox();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_View, m_Proj;
		glm::vec3 m_Translation;

		float incTranslationX;
		float incTranslationY;
		float inc;

		float slideSpeed;
		int directionX;
		int directionY;
	};

}