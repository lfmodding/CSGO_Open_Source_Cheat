#pragma once
#include <Windows.h>

inline HMODULE dllModule;

namespace systemMetrics
{
	inline int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	inline int screenHeight = GetSystemMetrics(SM_CYSCREEN);
}