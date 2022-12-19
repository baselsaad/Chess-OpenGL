#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


class Debug
{
public:
	static void Init();

	template<typename...Args>
	static void Log(const Args&... args)
	{
		Debug::GetLogger()->info(args ...);
	}

	template<typename...Args>
	static void Info(const Args&... args)
	{
		Debug::GetLogger()->info(args ...);
	}

	template<typename...Args>
	static void Warn(const Args&... args)
	{
		Debug::GetLogger()->warn(args ...);
	}

	template<typename...Args>
	static void Error(const Args&... args)
	{
		Debug::GetLogger()->error(args ...);
	}

	template<typename...Args>
	static void Critical(const Args&... args)
	{
		Debug::GetLogger()->critical(args ...);
	}

	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};



#define ASSERT_ERROR(...)		::Debug::GetLogger()->error(__VA_ARGS__);