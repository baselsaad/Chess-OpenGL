#include "pch.h"
#include "OpenGL-Core.h"
#include "App.h"

#include "Event.h"
#include "Game.h"
#include "Renderer\Defaults.h"
#include "Utilities\Log.h"
#include "Utilities\Debug.h"
#include "Utilities\Timer.h"

static bool s_Running = false;

Application::Application()
	: m_Game(nullptr)
{
	WindowData data;
	data.Width = Defaults::WINDOW_WIDTH;
	data.Height = Defaults::WINDOW_HEIGHT;
	data.Title = "Chess";

	m_Window = new OpenGLWindow(data);
	m_Window->SetVsync(true);

	Renderer::Init({ data.Width,data.Height });

	Debug::Info("Width {}, Height {}", data.Width, data.Height);
}

Application::~Application()
{
	delete m_Window;
	delete m_Game;
	Renderer::ShutDown();
}

void Application::OnStart()
{
	s_Running = true;
	SetupEventCallback();

	m_PlayerInput.BindActionEvent(EventType::CloseWindow, this, &Application::OnClose);
	m_PlayerInput.BindActionEvent(EventType::ResizeWindow, this, &Application::OnResizeWindow);

	m_Game = new Game(m_Window->GetWindowHeight(), m_Window->GetWindowWidth());
	m_Game->OnStart();
	m_Game->SetupPlayerInput(m_PlayerInput);
}

void Application::Run()
{
	// OnStart
	{
		OnStart();
	}

	// OnUpdate
	while (s_Running)
	{
		m_DeltaTime.Update();
		Renderer::ResetStats();

		m_Window->Clear();
		m_Window->PollEvents();
		{
			m_Game->OnUpdate(m_DeltaTime);
		}
		m_Window->Swap();

		Debug::Log("Vsync: {0}, FPS ({2} ms): {1}, DrawCalls: {3}", 
			m_Window->IsVsyncOn(),
			m_DeltaTime.GetFramePerSecounds(),
			m_DeltaTime.GetMilliSeconds(),
			Renderer::GetDrawCalls());
	}

	// OnDestroy
	{
		OnDestroy();
	}
}

void Application::OnDestroy()
{
	m_Game->OnDestroy();
}

void Application::OnClose(CloseWindowEvent& event)
{
	s_Running = false;
}

void Application::OnResizeWindow(ResizeWindowEvent& event)
{
	Renderer::UpdateViewport(event.GetWidth(), event.GetHeight());
	
	m_Window->UpdateWindowSize(event.GetWidth(), event.GetHeight());
	m_Game->OnUpdateViewport();

	//Debug::Info("Resize: Width {}, Height {}",event.GetWidth(),event.GetHeight());
}

void Application::SetupEventCallback()
{
	m_EventCallback = [this](Event& e) -> void { m_PlayerInput.OnEvent(e); };
	glfwSetWindowUserPointer(*m_Window, &m_EventCallback);

	// Window Close 
	{
		auto callback = [](GLFWwindow* window)
		{
			auto& func = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			CloseWindowEvent e;
			func(e);
		};

		glfwSetWindowCloseCallback(*m_Window, callback);
	}

	// Window Resize
	{
		auto callback = [](GLFWwindow* window, int width, int height)
		{
			auto& func = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			ResizeWindowEvent event(width, height);
			func(event);
		};

		glfwSetWindowSizeCallback(*m_Window, callback);
	}

	// Mouse Buttons
	{
		auto callback = [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& func = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			double outX, outY;
			glfwGetCursorPos(window, &outX, &outY);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button, outX, outY);
					func(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button, outX, outY);
					func(event);
					break;
				}
			}
		};

		glfwSetMouseButtonCallback(*m_Window, callback);
	}

	// Mouse Move
	{
		auto callback = [](GLFWwindow* window, double x, double y)
		{
			auto& func = *(EventFuncType*)glfwGetWindowUserPointer(window);

			MouseMoveEvent event((float)x, (float)y);
			func(event);
		};

		glfwSetCursorPosCallback(*m_Window, callback);
	}

}