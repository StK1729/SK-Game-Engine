#pragma once


#ifdef SKGE_PLATFORM_WINDOWS
	#ifdef SKGE_BUILD_DLL
		#define SKGE_API __declspec(dllexport)
	#else
		#define SKGE_API __declspec(dllimport)
	#endif
#endif

#define BIT(x) ( 1 << x )

#ifdef SKGE_ENABLE_ASSERTS
	#define SKGE_CORE_ASSERT(x, ...) { if(!(x)) {SKGE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SKGE_CLIENT_ASSERT(x, ...) { if(!(x)) {SKGE_CLIENT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SKGE_CORE_ASSERT(x, ...)
	#define SKGE_CLIENT_ASSERT(x, ...)
#endif

#define SKGE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)