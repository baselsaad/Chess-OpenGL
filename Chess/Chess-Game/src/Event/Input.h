#pragma once
#include "Event.h"
#include "glm\vec2.hpp"

class OpenGLWindow;

class Input
{
public:
	static bool IsMouseButtonDown(const MouseButtonKey& key);
	static bool IsMouseButtonUp(const MouseButtonKey& key);
	static glm::vec2 GetMousePosition();
	
private:
	static void Init(OpenGLWindow* window);
	friend class Application;
};
