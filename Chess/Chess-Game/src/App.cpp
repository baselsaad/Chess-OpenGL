#include "pch.h"
#include "App.h"

#include "Event.h"
#include "PlayerInput.h"
#include "Game.h"

#include "Utilities\Log.h"
#include "Utilities\Colors.h"
#include "Utilities\Debug.h"

#include "Renderer\Window.h"
#include "Renderer\Renderer.h"
#include "Renderer\Shader.h"
#include "Renderer\Texture.h"
#include "Renderer\VertexArray.h"
#include "Renderer\VertexBuffer.h"
#include "Renderer\VertexBufferLayout.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\OpenGL.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

static bool s_Running = false;

Application::Application()
{
	WindowData data;
	data.Width = 960;
	data.Height = 540;
	data.Title = "Chess";

	m_Window = std::make_unique<OpenGLWindow>(data);
	m_PlayerInput = std::make_unique<PlayerInput>();
}

Application::~Application()
{
}

void Application::OnStart()
{
	SetupEventCallback();
	s_Running = true;

	m_PlayerInput->BindActionEvent(EventType::CloseWindow, this, &Application::OnClose);
	m_PlayerInput->BindActionEvent(EventType::ResizeWindow, this, &Application::OnResizeWindow);

	m_GameLayer = new Game();
	m_GameLayer->OnStart();
	m_GameLayer->SetupPlayerInput(m_PlayerInput.get());
}

void Application::Run()
{
	//OnStart
	{
		OnStart();
		ASSERT(m_GameLayer, "m_GameLayer obj can not be null!");
	}

	//OnUpdate (Game Loop)
	while (s_Running)
	{
		float now = (float)glfwGetTime() * 1000.0f;
		float frameTime = now - m_LastFrameTime;
		m_LastFrameTime = now;

		m_Window->PollEvents();
		m_Window->Clear();

		//Render
		{
			m_GameLayer->OnUpdate(frameTime); 
			m_GameLayer->OnRender();
		}

		m_Window->Swap();
	}

	//OnDestroy
	{
		OnDestroy();
	}
}

void Application::OnDestroy()
{
	m_GameLayer->OnDestroy();
	delete m_GameLayer;
}

void Application::OnClose(Event& event)
{
	ASSERT(event.GetEventType() == EventType::CloseWindow, "Wrong Event Type!!");
	s_Running = false;
}

void Application::OnResizeWindow(Event& event)
{
	ASSERT(event.GetEventType() == EventType::ResizeWindow, "Wrong Event Type!!");
	ResizeWindowEvent* e = static_cast<ResizeWindowEvent*>(&event);

	glViewport(0, 0, e->GetWidth(), e->GetHeight());

	m_Window->SetWindowWidth(e->GetWidth());
	m_Window->SetWindowHeight(e->GetHeight());

	//Debug::Error("OnResizeWindow");
}

void Application::SetupEventCallback()
{
	m_EventCallback = [this](Event& e) { m_PlayerInput->OnEvent(e); };
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