#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <TlHelp32.h>
#include <iostream>

#include "../globals.h"

#include "../Dependencies/imgui/imgui.h"
#include "../Dependencies/imgui/imgui_impl_win32.h"
#include "../Dependencies/imgui/imgui_impl_dx9.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "../Dependencies/detours/detours.h"
#pragma comment(lib, "detours.lib")

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

namespace DX9Hook
{
	inline EndScene oEndScene = NULL;
	inline WNDPROC oWndProc;
	inline HWND window = NULL;
	inline bool initialised = false;
	inline bool showWindow = true;

	bool SetupHook(EndScene* oEndScene, void* hkEndScene);
	bool Shutdown(EndScene* oEndScene, void* hkEndScene);

	void NewFrame(EndScene* oEndScene, void* hkEndScene, LPDIRECT3DDEVICE9 pDevice);
	void EndFrame();
}


