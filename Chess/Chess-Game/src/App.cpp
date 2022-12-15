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
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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

	m_BindFunctions[EventType::CloseWindow] = BIND_EVENT_FN(Application::OnClose);
	m_BindFunctions[EventType::ResizeWindow] = BIND_EVENT_FN(Application::OnResizeWindow);

	m_BindFunctions[EventType::MouseButtonePressed] = BIND_EVENT_FN(Application::OnMousePressed);
	m_BindFunctions[EventType::MouseButtoneReleased] = BIND_EVENT_FN(Application::OnMouseReleased);
	m_BindFunctions[EventType::MouseMove] = BIND_EVENT_FN(Application::OnMouseMove);

	// VertexBuffer
	VertexBuffer vertexBuffer(Defaults::positions, Defaults::PositionsSize * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	// VertexArray
	VertexArray vertexArray;
	vertexArray.AddBuffer(vertexBuffer, layout);

	//IndexBuffer
	IndexBuffer indexBuffer(Defaults::indices, Defaults::IndicesCount);

	// Shaders
	Shader shader("res/shaders/Color.shader");
	shader.Bind();

	Renderer renderer;

	while (s_Running)
	{
		m_Window->Clear();

		//Render
		{
			shader.Bind();

			const glm::mat4 proj = glm::ortho(0.0f, (float)m_Window->GetWindowWidth(), 0.0f, (float)m_Window->GetWindowHeight(), -1.0f, 1.0f);
			const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			glm::mat4 model = glm::translate(glm::mat4(1.0f), DEFAULT_TRANSFORM);
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f("u_MVP", mvp);
			shader.SetUniform4f("u_Color", Colors::White.R, Colors::White.G, Colors::White.B, Colors::White.Alpha);

			renderer.Draw(vertexArray, indexBuffer);
		}

		m_Window->Swap();
	}

}

void Application::InitEventSystem()
{
	m_EventCallback = BIND_EVENT_FN(Application::OnEvent);
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

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					func(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
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
	ASSERT(event.GetEventType() == EventType::CloseWindow, "Wrong Categroy!!");

	s_Running = false;
}

void Application::OnResizeWindow(Event& event)
{
	ASSERT(event.GetEventType() == EventType::ResizeWindow, "Wrong Categroy!!");
	ResizeWindowEvent* e = static_cast<ResizeWindowEvent*>(&event);

	glViewport(0, 0, e->GetWidth(), e->GetHeight());

	m_Window->SetWindowWidth(e->GetWidth());
	m_Window->SetWindowHeight(e->GetHeight());

	//Debug::Error("OnResizeWindow");
}

void Application::OnMousePressed(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonePressed, "Wrong Categroy!!");

	MouseButtonPressedEvent* pressed = static_cast<MouseButtonPressedEvent*>(&event);
	//Debug::Warn("MousePressed {0}", pressed->GetButton());
}

void Application::OnMouseReleased(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtoneReleased, "Wrong Categroy!!");

	MouseButtonReleasedEvent* pressed = static_cast<MouseButtonReleasedEvent*>(&event);
	//Debug::Warn("MouseButtonReleasedEvent");
}

void Application::OnMouseMove(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseMove, "Wrong Categroy!!");

	MouseMoveEvent* e = static_cast<MouseMoveEvent*>(&event);
	//Debug::Warn("X: {0}, Y : {1}", e->GetXPos(), e->GetYPos());
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
