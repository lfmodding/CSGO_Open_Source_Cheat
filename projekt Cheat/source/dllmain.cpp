#include "core/Hooks/Dx9Hook.h"
#include "globals.h"
#include "menu.h"
#include "core/NetVars/NetVarManager/NetVarManager.h"
#include "core/Interfaces/interfaceManager.h"
#include "globals.h"

EndScene oEndScene = NULL;

long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
    DX9Hook::NewFrame(&oEndScene, &hkEndScene, pDevice);

    if (DX9Hook::showWindow)
        menu::render();

    DX9Hook::EndFrame();
    return oEndScene(pDevice);
}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        dllModule = hModule;
        InterfaceManager::SetupInterfaces();
        SetupNetvars();
        initGlobals();
        DX9Hook::SetupHook(&oEndScene, &hkEndScene);
        DisableThreadLibraryCalls(hModule);
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

