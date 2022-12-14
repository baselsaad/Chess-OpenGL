#include "pch.h"
#include "Utilities\Log.h"

#include "Renderer\Window.h"
#include "Renderer\Renderer.h"

static bool s_Running = false;

class Application
{
public:
	Application()
	{
		Debug::Init();

		WindowData data;
		data.Width = 960;
		data.Height = 540;
		data.Title = "Chess";

		m_Window = OpenGLWindow(data);
	}

	~Application()
	{
		OpenGLContext::ShutDown();
	}

	void Run()
	{
		s_Running = true;
		Renderer renderer(&m_Window);

		while (s_Running)
		{
			//Render
		}
	}


private:
	OpenGLWindow m_Window;
};


int main()
{
	Application app;
	app.Run();
}

