#pragma once

#include "tests/Test.h"
#include "Renderer.h"

#include <memory>

namespace test
{
	class TestCircleOptimized : public Test
	{
	public:
		TestCircleOptimized();
		~TestCircleOptimized();

		void OnRender() override;
		void OnUpdate(float deltaTime) override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};
}