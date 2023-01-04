#include "interfaceManager.h"


class InterfaceReg
{
public:
	BYTE			createfn[4];
	const char* name;
	InterfaceReg* next;
};

template <typename T>
T* GetInterface(const char* name, const char* library)
{
	if (Interfaces.empty())
		return nullptr;

	std::string path = std::format("{}->{}", library, name);
	const char* fullName = Interfaces[fnv::Hash(path.c_str())].c_str();

	if (!fullName)
		return nullptr;

	const auto handle = GetModuleHandle(library);

	if (!handle)
		return nullptr;

	const auto functionAddress = GetProcAddress(handle, "CreateInterface");

	if (!functionAddress)
		return nullptr;

	using Fn = T * (*)(const char*, int*);

	const auto CreateInterface = reinterpret_cast<Fn>(functionAddress);

	return CreateInterface(fullName, nullptr);
}

bool DumpInterfaces(const char* baseName)
{
	void* createInterface = GetProcAddress(GetModuleHandleA(baseName), "CreateInterface");

	if (!createInterface)
		return false;

	uintptr_t createinterface = reinterpret_cast<uintptr_t>(GetProcAddress(GetModuleHandleA(baseName), "CreateInterface"));

	if (*reinterpret_cast<uint8_t*>(createinterface + 4) != 0xE9)
		return false;


	auto var01 = ((uintptr_t)createInterface + 0x8);
	if (!var01) return false;

	auto var02 = *(unsigned short*)((uintptr_t)createInterface + 0x5);
	if (!var02) return false;

	auto var03 = *(unsigned short*)((uintptr_t)createInterface + 0x7);
	if (!var03) return false;

	auto var04 = (uintptr_t)(var01 + (var02 - var03));
	if (!var04) return false;

	InterfaceReg* interface_registry = **(InterfaceReg***)(var04 + 0x6);
	if (!interface_registry) return false;

	for (InterfaceReg* curr = interface_registry; curr; curr = curr->next)
	{
		if (!curr->name)
			continue;

		auto fullName = std::format("{}->{}", baseName, curr->name);
		fullName.resize(fullName.size() - 3);

		if (!Interfaces[fnv::Hash(fullName.c_str())].empty())
			continue;

		Interfaces[fnv::Hash(fullName.c_str())] = curr->name;
		std::cout << fullName << std::endl << std::endl;
	}
	return true;

}

bool DumpInterfaces()
{
	HMODULE hMods[1024];
	HANDLE hProcess = GetCurrentProcess();
	DWORD cbNeeded;
	std::cout << "setup Interfaces called" << std::endl;
	if (EnumProcessModules(hProcess, hMods, sizeof(hMods) - 1, &cbNeeded))
	{
		for (int i = 0; i < ((cbNeeded / sizeof(HMODULE))); i++)
		{
			TCHAR baseName[MAX_PATH];
			if (GetModuleBaseNameA(hProcess, hMods[i], baseName, sizeof(baseName) / sizeof(TCHAR)))
			{
				if (baseName)
					DumpInterfaces(baseName);
			}
		}
	}
	return true;
}

void InitInterfaces()
{
	entityList = GetInterface<IClientEntityList>("VClientEntityList", "client.dll");
	client = GetInterface<IClient>("VClient", "client.dll");
}

bool InterfaceManager::SetupInterfaces()
{
	DumpInterfaces();
	InitInterfaces();
	return true;
}



