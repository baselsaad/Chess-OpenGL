#include "pch.h"
#include "DeltaTime.h"


void DeltaTime::Update()
{
	float now = (float)glfwGetTime();
	m_FrameTime = now - m_LastFrameTime;
	m_LastFrameTime = now;
}

