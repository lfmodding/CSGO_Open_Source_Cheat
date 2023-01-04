#pragma once
#include <Windows.h>
#include "core/Interfaces/interfaces.h"

inline HMODULE dllModule;

namespace systemMetrics
{	
	inline int screenWidth;
	inline int screenHeight;
}

inline void initGlobals()
{
	engineClient->GetScreenSize(systemMetrics::screenWidth, systemMetrics::screenHeight);
}