#pragma once
#include <memory>


#ifdef SKGE_PLATFORM_WINDOWS
	#ifdef DLL
	#ifdef SKGE_BUILD_DLL
		#define SKGE_API __declspec(dllexport)
	#else
		#define SKGE_API __declspec(dllimport)
	#endif
	#endif
	#define SKGE_API
#endif

#define BIT(x) ( 1 << x )

#ifdef SKGE_DEBUG
	#define SKGE_ENABLE_ASSERTS
#endif

#ifdef SKGE_ENABLE_ASSERTS
	#define SKGE_CORE_ASSERT(x, ...) { if(!(x)) {SKGE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SKGE_CLIENT_ASSERT(x, ...) { if(!(x)) {SKGE_CLIENT_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SKGE_CORE_ASSERT(x, ...)
	#define SKGE_CLIENT_ASSERT(x, ...)
#endif

#define SKGE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace SK_Game_Engine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}