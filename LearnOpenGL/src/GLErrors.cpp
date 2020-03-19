#include <iostream>
#include "GLErrors.h"

void GLClearError()
{
	while (glGetError());
}

bool GLLogCall(const char* function, const char* file, const int& line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << "\n";
		return false;
	}
	return true;
}