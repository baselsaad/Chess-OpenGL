#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if (!(x)) __debugbreak();

#define CHECK(x, Msg)								\
		if (!(x))									\
		{											\
			std::cout<< "\n"<< Msg << std::endl;	\
			__debugbreak();							\
		}

// compatible with all OpenGL Versions
#define GL_CALL(x)									\
	GlClearErros();									\
	x;												\
	ASSERT(GlLogCall(#x, __FILE__, __LINE__))

static void GlClearErros()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GlLogCall(const char* functionName, const char* fileName, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << fileName << ": " << functionName << " at Line (" << line << ")" << std::endl;
		printf("OpenGL-Error: %.6x (%d)", error, error);

		return false;
	}


	return true;
}


static void OpenGLMessageCallback(
	unsigned source,
	unsigned type,
	unsigned id,
	unsigned severity,
	int length,
	const char* message,
	const void* userParam)
{

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:         std::cout << "CRITICAL: " << message << std::endl;		return;
		case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "ERROR: " << message << std::endl;		return;
		case GL_DEBUG_SEVERITY_LOW:          std::cout << "WARN: " << message << std::endl;			return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: /*std::cout << "TRACE: " << message << std::endl;*/	return;
	}

	ASSERT(false);
}