#include "pch.h"
#include "OpenGL-Core.h"
#include "App.h"

#include "Event.h"
#include "PlayerInput.h"
#include "Game.h"
#include "Renderer\Defaults.h"

#include "Utilities\Log.h"
#include "Utilities\Debug.h"
#include "Utilities\Timer.h"

static bool s_Running = false;

Application::Application()
	: m_GameLayer(nullptr)
{
	WindowData data;
	data.Width = Defaults::WINDOW_WIDTH;
	data.Height = Defaults::WINDOW_HEIGHT;
	data.Title = "Chess";

	m_Window = new OpenGLWindow(data);
	Renderer::Init({ data.Width,data.Height });

	m_PlayerInput = new PlayerInput();
}

Application::~Application()
{
	delete m_Window;
	delete m_PlayerInput;
	delete m_GameLayer;
	Renderer::ShutDown();
}

void Application::OnStart()
{
	SetupEventCallback();
	s_Running = true;

	m_PlayerInput->BindActionEvent(EventType::CloseWindow, this, &Application::OnClose);
	m_PlayerInput->BindActionEvent(EventType::ResizeWindow, this, &Application::OnResizeWindow);

	m_GameLayer = new Game(m_Window->GetWindowHeight(), m_Window->GetWindowWidth());
	m_GameLayer->OnStart(m_EntityContainer);
	m_GameLayer->SetupPlayerInput(m_PlayerInput);
}

void Application::Run()
{
	// OnStart
	{
		OnStart();
	}

	// OnUpdate (Game Loop)
	while (s_Running)
	{
		m_DeltaTime.Update();
		Renderer::ResetStats();

		m_Window->Clear();
		m_Window->PollEvents();
		{
			m_GameLayer->OnUpdate(m_DeltaTime);
			m_EntityContainer.OnRender();

			Debug::Log("DrawCalls {0}", Renderer::GetDrawCalls());
			Debug::Log("FPS {0}", m_DeltaTime.GetFramePerSecounds());
		}
		m_Window->Swap();
	}

	// OnDestroy
	{
		OnDestroy();
	}
}

void Application::OnDestroy()
{
	m_GameLayer->OnDestroy();
}

void Application::OnClose(CloseWindowEvent& event)
{
	s_Running = false;
}

void Application::OnResizeWindow(ResizeWindowEvent& event)
{
	glViewport(0, 0, event.GetWidth(), event.GetHeight());

	m_Window->UpdateViewport(event.GetWidth(), event.GetHeight());
	m_GameLayer->OnUpdateViewport(event.GetWidth(), event.GetHeight());
	Renderer::UpdateViewport(event.GetWidth(), event.GetHeight());
}

void Application::SetupEventCallback()
{
	m_EventCallback = [this](Event& e) -> void { m_PlayerInput->OnEvent(e); };
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