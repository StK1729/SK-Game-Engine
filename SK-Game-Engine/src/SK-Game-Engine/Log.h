#pragma once
#include "Core.h"
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"


namespace SK_Game_Engine{
	class SKGE_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_core_logger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_client_logger; };
		void LogInfo(std::string& message);
		void LogWarning(std::string& message);
		void LogError(std::string& message);
		void LogDebug(std::string& message);
	private :
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};
}

#define SKGE_CORE_TRACE(...) ::SK_Game_Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SKGE_CORE_INFO(...) ::SK_Game_Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SKGE_CORE_WARN(...) ::SK_Game_Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SKGE_CORE_ERROR(...) ::SK_Game_Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SKGE_CORE_CRITICAL(...) ::SK_Game_Engine::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define SKGE_CLIENT_TRACE(...) ::SK_Game_Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SKGE_CLIENT_INFO(...) ::SK_Game_Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define SKGE_CLIENT_WARN(...) ::SK_Game_Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SKGE_CLIENT_ERROR(...) ::SK_Game_Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define SKGE_CLIENT_CRITICAL(...) ::SK_Game_Engine::Log::GetClientLogger()->critical(__VA_ARGS__)
