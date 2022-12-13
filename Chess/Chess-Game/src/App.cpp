#include "pch.h"
#include "Renderer\Renderer.h"
#include "Utilities\Log.h"

int main()
{
	Debug::Init();

	Debug::Log("Hello World");
	Debug::Info("Hello World");
	Debug::Warn("Hello World");
	Debug::Error("Hello World");
	Debug::Critical("Hello World");
}