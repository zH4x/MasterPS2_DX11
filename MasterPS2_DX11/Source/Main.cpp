#include <time.h>

#include "EventManager.h"
#include "Inputs.h"
#include "Options.h"
#include "TEST.h"


#include "D3D11/d3d11hook.h"
#include "SDK/CGame.h"

const LPCSTR WINDOW_CLASS_NAME = "Planetside2 PlayClient (Stage) x64";

#define PAUSE(msg)\
	printf("[INFO] %s\n", msg);\
	system("pause");

#define UPDATE_DELAY 0.01

clock_t lastUpdate = clock();

void WaitForPlayerInGame()
{
	printf("Waiting for player in game ...\n");
	while (!CGameInstance::Get())
	{
		Sleep(500);
		putchar('.');
		while (!CGameInstance::GetFirstObject() && !CGameInstance::GetFirstObject()->m_playerBase)
		{
			Sleep(1000);
			putchar('.');
		}
	}
	putchar('\n');
	system("cls"); // clear console
}

void InitializeConsole()
{
	AllocConsole();
	auto res = freopen("CONOUT$", "w", stdout);
	system("title MasterPS2 debug console");
}

#include "Features/Misc.h"
#include "Features/Noclip.h"
#include "Features/Aimbot.h"
#include "Features/ESP.h"
void InitializeComponents()
{
	Misk::Initialize();
	Noclip::Initialize();
	Aimbot::Initialize();
	ESP::Initialize();
}

void ShutdownComponents()
{
	D3D11Hook::Shutdown();
	InputSys::Get().Shutdown();
}

void InitializeHotKeys()
{
	InputSys::Get().RegisterHotkey(VK_F1, []()
		{
			__try { TEST::test1(); }
			__except (1) { std::cout << "[Error] inside function TEST" << std::endl; }
		});

	InputSys::Get().RegisterHotkey(VK_F2, []()
		{
			__try { TEST::testGraphics(); }
			__except (1) { std::cout << "[Error] inside function testMatrix" << std::endl; }
		});

	InputSys::Get().RegisterHotkey(VK_F3, []()
		{
			__try { TEST::testMatrix(); }
			__except (1) { std::cout << "[Error] inside function testMatrix" << std::endl; }
		});
}

DWORD WINAPI MainThread(LPVOID hModule)
{
	InitializeConsole();

	printf("[INFO] Initializing MasterPS2 !\n");
	//PAUSE("Waiting for injection !");

	WaitForPlayerInGame();

	HWND hTargetWindow = FindWindow(WINDOW_CLASS_NAME, NULL);
	if (!hTargetWindow)
	{
		printf("Error : Could not find window class name : %s", WINDOW_CLASS_NAME);
		goto cleanup;
	}

	InputSys::Get().Initialize(hTargetWindow);
	D3D11Hook::Initialize((HMODULE)hModule, hTargetWindow);

	InitializeComponents();
	InitializeHotKeys();

	// Update Loop
	while (!InputSys::Get().IsKeyDown(VK_END))
	{
		if (g_Options.noclip && g_Options.noclip_active)
			Noclip::OnFastUpdate();

		if (float(clock() - lastUpdate) / CLOCKS_PER_SEC > UPDATE_DELAY)
		{
			lastUpdate = clock();
			EventHandler<EventIndex::OnUpdate, EventDefines::OnUpdate, int>::GetInstance()->Trigger(NULL);
		}
	}

cleanup:
	ShutdownComponents();

	Beep(523, 250);
	Sleep(250);
	FreeConsole();
	FreeLibraryAndExitThread(static_cast<HMODULE>(hModule), 1);
	return false;
}

BOOL WINAPI OnDllDetach()
{
	return TRUE;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
		return TRUE;
	case DLL_PROCESS_DETACH:
		return OnDllDetach();
		return TRUE;
	default:
		return TRUE;
	}
	return TRUE;
}