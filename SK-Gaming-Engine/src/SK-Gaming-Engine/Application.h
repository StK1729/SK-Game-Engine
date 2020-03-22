#pragma once

#include "Core.h"

namespace SK_Gaming_Engine {

	SKGE_API class Application {
	public:
		SKGE_API Application();
		SKGE_API virtual ~Application();
		SKGE_API void Run();
	};

	Application* CreateApplication();
}