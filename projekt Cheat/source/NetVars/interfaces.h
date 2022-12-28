#pragma once
#include <Windows.h>
#include "..\SDK\ClientInterface.h"

template <typename T>
T* GetInterface(const char* name, const char* library)
{
	const auto handle = GetModuleHandle(library);

	if (!handle)
		return nullptr;

	const auto functionAddress = GetProcAddress(handle, "CreateInterface");

	if (!functionAddress)
		return nullptr;

	using Fn = T * (*)(const char*, int*);

	const auto CreateInterface = reinterpret_cast<Fn>(functionAddress);

	return CreateInterface(name, nullptr);
}

inline IClientEntityList* entityList = nullptr;
inline IClient* client = nullptr;