#include "pch.h"

#include "App.h"
#include "Utilities\Debug.h"

static bool s_AppRunning = true;

int main()
{
#if _MSC_VER
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Debug::Init();
	Application* app = new Application();
	app->Run();
	delete app;
	Debug::ShutDown();

	return 0;
}

