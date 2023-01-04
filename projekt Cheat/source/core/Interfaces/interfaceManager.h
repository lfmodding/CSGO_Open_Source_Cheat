#pragma once
#include <iostream>
#include <Windows.h>
#include <psapi.h>
#include <format>
#include <unordered_map>

#include "..\..\SDK\ClientInterface.h"
#include "..\..\SDK\EngineInterface.h"

#include "..\..\Dependencies\fnv.h"
#include "interfaces.h"

inline std::unordered_map<std::uint32_t, std::string> Interfaces;


namespace InterfaceManager
{
	bool SetupInterfaces();
}


