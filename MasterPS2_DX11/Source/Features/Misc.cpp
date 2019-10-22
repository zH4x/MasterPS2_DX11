#include "Misc.h"

#include "..\Options.h"
#include "..\SDK\SDKInclude.h"
#include "..\EventManager.h"
#include "..\Inputs.h"

void Misk::Initialize()
{
	InputSys::Get().RegisterHotkey(VK_RIGHT, []()
		{
			if (g_Options.speedhack_velocity < 25)
				++g_Options.speedhack_velocity;
		});

	InputSys::Get().RegisterHotkey(VK_LEFT, []()
		{
			if (g_Options.speedhack_velocity > 1)
				--g_Options.speedhack_velocity;
		});

	EventHandler<EventIndex::OnUpdate, EventDefines::OnUpdate, int>::GetInstance()->Add(Misk::OnUpdate);
}

void Misk::OnUpdate(int)
{
	CEntity* localPlayer = CGameInstance::GetFirstObject();
	if (!localPlayer)
		return;

	g_Options.speedhack ? SetGroundSpeed(g_Options.speedhack_velocity) : localPlayer->SetGroundSpeed(4.f);
}

void Misk::SetGroundSpeed(float speed)
{
	*reinterpret_cast<float*>(oGroundSpeed) = speed;
}




