#include "pch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Debug::s_Logger;

void Debug::Init()
{

#if DIST
	// (Date) (Thread) (LogLvel) [Message]
	spdlog::set_pattern("%^[%d-%m-%Y %S:%M:%H] [%n] [%t] [%l]: %v%$");
#else
	spdlog::set_pattern("%^[%n] [%t] [%l]: %v%$");
#endif

	s_Logger = spdlog::stdout_color_mt("Chess-Log");
}