#include "pch.h"
#include "DeltaTime.h"


void DeltaTime::Update()
{
	// DeltaTime
	float now = glfwGetTime();
	m_FrameTime = (float)(now - m_LastFrameTime);
	m_LastFrameTime = glfwGetTime();
}

