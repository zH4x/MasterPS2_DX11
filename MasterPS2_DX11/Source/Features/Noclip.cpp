#include "Noclip.h"

#include "..\EventManager.h"
#include "..\Inputs.h"
#include "..\Options.h"

#include "..\SDK\SDKInclude.h"

# define PI           3.14159265358979323846f  /* pi */

bool doInit = true;
CEntity* localPlayer = nullptr;
Vector3 Noclip::CurrentPosition = Vector3(0, 0, 0);

int GetFowardFactor()
{
	int wsFactor = 0;
	if (InputSys::Get().IsKeyDown(0x57)) ++wsFactor;
	if (InputSys::Get().IsKeyDown(0x53)) --wsFactor;
	return wsFactor;
}

int GetSideFactor()
{
	int adFactor = 0;
	if (InputSys::Get().IsKeyDown(0x41)) ++adFactor;
	if (InputSys::Get().IsKeyDown(0x44)) --adFactor;
	return adFactor;
}

void Noclip::CalculateNewPosition()
{
	Vector3 angles = localPlayer->m_viewAngles;
	Vector3 fowardVector = (g_Options.noclip_speed + 1) * (float)GetFowardFactor() * (Vector3(std::sin(angles.x), std::sin(angles.y), std::cos(angles.x)) / 5.0f);
	angles += PI / 2;
	Vector3 sideVector = (g_Options.noclip_speed + 1) * (float)GetSideFactor() * (Vector3(std::sin(angles.x), 0, std::cos(angles.x)) / 5.0f);
	CurrentPosition += fowardVector + sideVector;
}

void Noclip::OnUpdate(int)
{
	if (!g_Options.noclip)
		return;

	if (!g_Options.noclip_active)
	{
		doInit = true;
		return;
	}

	if (doInit)
	{
		localPlayer = CGameInstance::GetFirstObject();
		if (!localPlayer || !localPlayer->m_playerBase) 
		{
			g_Options.noclip = false;
			g_Options.noclip_active = false;
			return;
		}
		CurrentPosition = localPlayer->m_playerBase->m_position;
		doInit = false;
	}

	CalculateNewPosition();
}

void Noclip::OnFastUpdate()
{
	if (!doInit)
		localPlayer->m_playerBase->ChangeServerPosition(CurrentPosition);
}

void Noclip::Initialize()
{
	InputSys::Get().RegisterHotkey(VK_OEM_3, []()
	{
		if (g_Options.noclip)
			g_Options.noclip_active = !g_Options.noclip_active;
	});

	InputSys::Get().RegisterHotkey(VK_UP, []()
	{
		if (g_Options.noclip_speed < 4)
			++g_Options.noclip_speed;
	});

	InputSys::Get().RegisterHotkey(VK_DOWN, []()
	{
		if (g_Options.noclip_speed > 0)
			--g_Options.noclip_speed;
	});

	EventHandler<EventIndex::OnUpdate, EventDefines::OnUpdate, int>::GetInstance()->Add(Noclip::OnUpdate);
}



//#include "Noclip.h"
//#include "SDK/SDKInclude.h"
//#include "EventManager.h"
//#include "Inputs.h"
//
//# define PI           3.14159265358979323846f  /* pi */
//
//bool doInit = true;
//CEntity* player = nullptr;
//Vector3 Noclip::CurrentPosition = Vector3(0, 0, 0);
//
//int GetFowardFactor()
//{
//	int wsFactor = 0;
//	if (GetAsyncKeyState(0x57)) ++wsFactor;
//	if (GetAsyncKeyState(0x53)) --wsFactor;
//	return wsFactor;
//}
//
//int GetSideFactor()
//{
//	int adFactor = 0;
//	if (GetAsyncKeyState(0x41)) ++adFactor;
//	if (GetAsyncKeyState(0x44)) --adFactor;
//	return adFactor;
//}
//
//void Noclip::CalculateNewPosition()
//{
//	Vector3 angles = player->m_viewAngles;
//	Vector3 fowardVector = (g_Options.noclip_speed + 1) * (float)GetFowardFactor() * (Vector3(std::sin(angles.x), std::sin(angles.y), std::cos(angles.x)) / 5.0f);
//	angles += PI / 2;
//	Vector3 sideVector = (g_Options.noclip_speed + 1) * (float)GetSideFactor() * (Vector3(std::sin(angles.x), 0, std::cos(angles.x)) / 5.0f);
//	CurrentPosition += fowardVector + sideVector;
//}
//
//void Noclip::OnUpdate(int)
//{
//	if (!g_Options.noclip)
//		return;
//
//	if (!g_Options.noclip_active)
//	{
//		doInit = true;
//		return;
//	}
//
//	if (doInit)
//	{
//		CurrentPosition = CNoclip::GetNoclipPosition();
//		player = CGame::GetFirstObject();
//		doInit = false;
//	}
//
//	if (!player)
//	{
//		g_Options.noclip = false;
//		g_Options.noclip_active = false;
//		return;
//	}
//
//	CalculateNewPosition();
//}
//
//void Noclip::OnFastUpdate()
//{
//	if (!doInit)
//		CNoclip::SetNoClipPosition(CurrentPosition);
//}
//
//void Noclip::Initialize()
//{
//	InputSys::Get().RegisterHotkey(VK_OEM_3, []()
//	{
//		if (g_Options.noclip)
//			g_Options.noclip_active = !g_Options.noclip_active;
//	});
//
//	InputSys::Get().RegisterHotkey(VK_UP, []()
//	{
//		if (g_Options.noclip_speed < 4)
//			++g_Options.noclip_speed;
//	});
//
//	InputSys::Get().RegisterHotkey(VK_DOWN, []()
//	{
//		if (g_Options.noclip_speed > 0)
//			--g_Options.noclip_speed;
//	});
//
//	EventHandler<EventIndex::OnUpdate, EventDefines::OnUpdate, int>::GetInstance()->Add(Noclip::OnUpdate);
//}
