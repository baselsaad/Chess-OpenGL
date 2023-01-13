#include "pch.h"
#include "OpenGL-Core.h"

#include "Utilities/Debug.h"
#include "App.h"

static bool s_AppRunning = true;

int main()
{
	#if _MSC_VER && DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif
	
	Debug::Init("Chess-Console");
	Application app;
	app.Run();

	return 0;
}
