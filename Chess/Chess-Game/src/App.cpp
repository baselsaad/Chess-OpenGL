#include "pch.h"
#include "App.h"

#include "Utilities\Log.h"
#include "Renderer\Window.h"
#include "Renderer\Renderer.h"
#include "Renderer\Shader.h"
#include "Renderer\Texture.h"
#include "Renderer\VertexArray.h"
#include "Renderer\VertexBuffer.h"
#include "Renderer\VertexBufferLayout.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\OpenGL.h"
#include "Utilities\Colors.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Event.h"

static bool s_Running = false;

Application::Application()
{
	Debug::Init(); // Init Logging Console

	WindowData data;
	data.Width = 960;
	data.Height = 540;
	data.Title = "Chess";

	m_Window = std::make_shared<OpenGLWindow>(data);
}

Application::~Application()
{
	Debug::Log("End ...");
}

void Application::Run()
{
	s_Running = true;
	InitEventSystem();

	BindActionEvent(EventType::CloseWindow, std::bind(&Application::OnClose, this, std::placeholders::_1));
	BindActionEvent(EventType::ResizeWindow, std::bind(&Application::OnResizeWindow, this, std::placeholders::_1));

	BindActionEvent(EventType::MouseButtonPressed, std::bind(&Application::OnMousePressed, this, std::placeholders::_1));
	BindActionEvent(EventType::MouseButtonReleased, std::bind(&Application::OnMouseReleased, this, std::placeholders::_1));

	while (s_Running)
	{
		m_Window->Clear();

		//Render
		{
		}

		m_Window->Swap();
	}

}

void Application::InitEventSystem()
{
	m_EventCallback = [this](Event& e) { OnEvent(e); };
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

void Application::OnMousePressed(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonPressed, "Wrong Event Type!!");

	MouseButtonPressedEvent* pressedButton = static_cast<MouseButtonPressedEvent*>(&event);

	Debug::Warn("MouseButton Pressed on X:{0}, Y:{1}", pressedButton->GetXPosition(), pressedButton->GetYPosition());
}

void Application::OnMouseReleased(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonReleased, "Wrong Event Type!!");

	MouseButtonReleasedEvent* releasedButton = static_cast<MouseButtonReleasedEvent*>(&event);
	Debug::Error("MouseButton Released on X:{0}, Y:{1}", releasedButton->GetXPosition(), releasedButton->GetYPosition());
}

void Application::OnMouseMove(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseMove, "Wrong Event Type!!");

	MouseMoveEvent* e = static_cast<MouseMoveEvent*>(&event);
	//Debug::Warn("X: {0}, Y : {1}", e->GetXPos(), e->GetYPos());
}

void Application::BindActionEvent(EventType inputEvent, EventFuncType&& func)
{
	m_BindFunctions[inputEvent] = std::move(func);
}

void Application::OnEvent(Event& event)
{
	auto finder = m_BindFunctions.find(event.GetEventType());
	if (finder != m_BindFunctions.end())
	{
		auto& func = finder->second;
		func(event);
	}
}
