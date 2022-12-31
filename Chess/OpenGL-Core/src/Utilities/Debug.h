#pragma once
#include "Utilities\Log.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#if DEBUG

#define ASSERT(x, Msg)								\
		if (!(x))									\
		{											\
			ASSERT_ERROR(Msg);						\
			__debugbreak();							\
		}
#else
#define ASSERT(x,MSG)
#endif

#define CHECK(x) if (!(x)) __debugbreak();

static void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity,
	int length, const char* message, const void* userParam)
{

	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:			Debug::Critical(message);		return;
		case GL_DEBUG_SEVERITY_MEDIUM:			Debug::Error(message);			return;
		case GL_DEBUG_SEVERITY_LOW:				Debug::Warn(message);			return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	return;
	}

	ASSERT(false, "Unkown severity!!");
}

static void GLFWErrorCallback(int error, const char* desc)
{
	Debug::Error("Error {0}: {1}", error, desc);
}