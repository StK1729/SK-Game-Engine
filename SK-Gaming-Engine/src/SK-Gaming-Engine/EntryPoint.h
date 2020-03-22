#pragma once
#include "Application.h"

#ifdef SKGE_PLATFORM_WINDOWS

extern SK_Gaming_Engine::Application* SK_Gaming_Engine::CreateApplication();

int main(int argc, char** argv)
{
	SK_Gaming_Engine::Application* app = SK_Gaming_Engine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif