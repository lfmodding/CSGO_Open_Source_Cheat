#include "Dx9Hook.h"

using namespace DX9Hook;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(DX9Hook::window);
	ImGui_ImplDX9_Init(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

bool HookEndScene(EndScene* oEndScene, void* hkEndScene)
{
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
		return false;

	D3DPRESENT_PARAMETERS d3dparams = { 0 };
	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow = GetForegroundWindow();
	d3dparams.Windowed = true;

	IDirect3DDevice9* pDevice = nullptr;

	HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dparams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dparams, &pDevice);
	if (FAILED(result) || !pDevice) {
		pD3D->Release();
		return false;
	}
	void** vTable = *reinterpret_cast<void***>(pDevice);

	*oEndScene = (EndScene)DetourFunction((PBYTE)vTable[42], (PBYTE)hkEndScene);

	pDevice->Release();
	pD3D->Release();
	return true;
}

bool DX9Hook::SetupHook(EndScene* oEndScene, void* hkEndScene)
{
	bool attached = false;
	do
	{
		if (HookEndScene(oEndScene, hkEndScene) == true)
		{
			do
				window = GetProcessWindow();
			while (window == NULL);
				oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
				attached = true;
		}
	} while (!attached);
	return true;
}

bool DX9Hook::Shutdown(EndScene* oEndScene, void* hkEndScene)
{
	DetourRemove((PBYTE)*oEndScene, (PBYTE)hkEndScene);
	return true;
}

void DX9Hook::NewFrame(EndScene* oEndScene, void* hkEndScene, LPDIRECT3DDEVICE9 pDevice)
{
	if (!initialised)
	{
		InitImGui(pDevice);
		initialised = true;
	}

	if (GetAsyncKeyState(VK_END)) {
		DX9Hook::Shutdown(oEndScene, hkEndScene);
		FreeLibrary(dllModule);
		return;
	}

	if ((GetAsyncKeyState(VK_INSERT) & 1))
	{
		showWindow = !showWindow;
	}

	using namespace systemMetrics;
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImDrawList* drawlist = ImGui::GetBackgroundDrawList();
	//20, 35
	ImVec2 Position = ImVec2(screenWidth - ((screenWidth / 20) * (2560 / screenWidth)), screenHeight - screenHeight / 35);
	drawlist->AddText(Position, ImColor(255, 0, 0), "Projekt Cheat");
}

void DX9Hook::EndFrame()
{
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
