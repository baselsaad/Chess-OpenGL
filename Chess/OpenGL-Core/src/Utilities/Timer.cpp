#include "pch.h"
#include "Timer.h"
#include <iostream>

#define MAX_SIZE 2

Timer::Timer()
	: m_IsTimerStarted(false)
{
	CallbacksVec.reserve(MAX_SIZE);
}

void Timer::StartTimer() const
{
	m_Start = std::chrono::high_resolution_clock::now();
	m_IsTimerStarted = true;
}

void Timer::StopTimer() const
{
	if (!m_IsTimerStarted)
	{
		m_ElapsedTime = 0.0f;
		return;
	}

	m_End = std::chrono::high_resolution_clock::now();
	m_Duration = m_End - m_Start;
	m_ElapsedTime = m_Duration.count();
	m_IsTimerStarted = false;
}

size_t Timer::SetCallBackTimer(float rate, const Lambda& callback)
{
	if (CallbacksVec.size() >= MAX_SIZE)
	{
		return -1;
	}


	size_t id = CallbacksVec.size();
	CallbacksVec.emplace_back(rate, callback);

	return id;
}

void Timer::ClearCallBackTimer(int id)
{
	CallbacksVec.erase(CallbacksVec.begin() + id);
}
