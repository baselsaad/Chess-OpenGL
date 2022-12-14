#include "pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Debug::s_Logger;

void Debug::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	s_Logger = spdlog::stdout_color_mt("GLCORE");
	s_Logger->set_level(spdlog::level::trace);
}