#include "pch.h"
#include "App.h"

int main()
{
	Application* app = new Application();
	app->Run();
	delete app;
}