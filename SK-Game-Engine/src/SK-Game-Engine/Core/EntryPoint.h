#pragma once

#ifdef SKGE_PLATFORM_WINDOWS

extern SK_Game_Engine::Application* SK_Game_Engine::CreateApplication();

int main(int argc, char** argv)
{
	SK_Game_Engine::Log::Init();
	SKGE_CORE_TRACE("Hello {0}", "Stefan Kraljevic");
	SKGE_CLIENT_INFO("Initialized client logger.");

	SKGE_PROFILING_BEGIN_SESSION("Startup", "startup.json");
	SK_Game_Engine::Application* app = SK_Game_Engine::CreateApplication();
	SKGE_PROFILING_END_SESSION();

	SKGE_PROFILING_BEGIN_SESSION("Runtime", "runtime.json");
	app->Run();
	SKGE_PROFILING_END_SESSION();

	SKGE_PROFILING_BEGIN_SESSION("Shutdown", "shutdown.json");
	delete app;
	SKGE_PROFILING_END_SESSION();
	return 0;
}
#endif