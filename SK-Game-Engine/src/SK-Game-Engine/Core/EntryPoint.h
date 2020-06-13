#pragma once

#ifdef SKGE_PLATFORM_WINDOWS

extern SK_Game_Engine::Application* SK_Game_Engine::CreateApplication();

int main(int argc, char** argv)
{
	SK_Game_Engine::Log::Init();
	SKGE_CORE_TRACE("Hello {0}", "Stefan Kraljevic");
	SKGE_CLIENT_INFO("Initialized client logger.");
	SK_Game_Engine::Application* app = SK_Game_Engine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif