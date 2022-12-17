#pragma once
#include "Utilities\Log.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define CHECK(x) if (!(x)) __debugbreak();

#define ASSERT(x, Msg)								\
		if (!(x))									\
		{											\
			ASSERT_ERROR(Msg);						\
			__debugbreak();							\
		}

// compatible with all OpenGL Versions
#define GL_CALL(x)									\
	GlClearErros();									\
	x;												\
	CHECK(GlLogCall(#x, __FILE__, __LINE__))

static void GlClearErros()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GlLogCall(const char* functionName, const char* fileName, int line)
{
	while (GLenum error = glGetError())
	{
		Debug::Error("{0} : {1} at Line ({0})", fileName, functionName, line);
		Debug::Error("OpenGL-Error: {0} {1}", error, error);

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
		case GL_DEBUG_SEVERITY_HIGH:			Debug::Critical(message);		return;
		case GL_DEBUG_SEVERITY_MEDIUM:			Debug::Error(message);			return;
		case GL_DEBUG_SEVERITY_LOW:				Debug::Warn(message);			return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	Debug::Log(message);			return;
	}

	ASSERT(false, "Unkown severity!!");
}

static void GLFWErrorCallback(int error, const char* desc)
{
	Debug::Error("Error {0}: {1}", error, desc);
}