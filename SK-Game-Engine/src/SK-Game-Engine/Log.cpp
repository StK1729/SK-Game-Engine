#include "pch.h"
#include "Log.h"

namespace SK_Game_Engine {

	std::shared_ptr<spdlog::logger> Log::s_core_logger;
	std::shared_ptr<spdlog::logger> Log::s_client_logger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_core_logger = spdlog::stdout_color_mt("SKGE");
		s_core_logger->set_level(spdlog::level::trace);
		s_client_logger = spdlog::stdout_color_mt("APP");
		s_client_logger->set_level(spdlog::level::trace);
	}

	void Log::LogInfo(std::string& message)
	{
		spdlog::info(message);
	}

	void Log::LogError(std::string& message)
	{
		spdlog::error(message);
	}

	void Log::LogWarning(std::string& message)
	{
		spdlog::warn(message);

	}

	void Log::LogDebug(std::string& message)
	{
		spdlog::debug(message);
	}
}
