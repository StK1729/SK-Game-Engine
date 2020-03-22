#pragma once


#ifdef SKGE_PLATFORM_WINDOWS
	#ifdef SKGE_BUILD_DLL
		#define SKGE_API __declspec(dllexport)
	#else
		#define SKGE_API __declspec(dllimport)
	#endif
#endif