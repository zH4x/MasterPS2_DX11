#include "Aimbot.h"

#include "..\SDK\SDKInclude.h"
#include "..\EventManager.h"
#include "..\Inputs.h"
#include "..\Options.h"
//#include "D3D11Render.h"

#include <iostream>


TargetInfo Aimbot::CurrentTarget;
bool Aimbot::isLock = false;

static float GetHeightFactor(CEntity* entity)
{
	switch (entity->m_stance)
	{
	case PlayerStance::Crouch:		return 0.60f;
	case PlayerStance::CrouchWalk:	return 0.60f;

	default: return 1;
	}
}

TargetInfo Aimbot::GetBestTarget()
{
	float width = CGameInstance::GetGraphics()->m_width;
	float height = CGameInstance::GetGraphics()->m_height;

	TargetInfo bestTarget = TargetInfo();

	float bestAngleLenght = FLT_MAX;
	Vector3 bestTargetScreenPosition = Vector3();

	CEntity* localPlayer = CGameInstance::GetFirstObject();
	Vector3 centerScreen = Vector3(width / 2, height / 2, 0);

	for (auto entity : CGameInstance::GetEntities())
	{
		TargetInfo aimbotTarget = GetTargetInfo(entity);

		if (!aimbotTarget.isInScreen || aimbotTarget.entity == nullptr)
			continue;

		float distTemp = aimbotTarget.screenPosition.DistTo(Vector3(width / 2, height / 2, 0));
		if (distTemp < g_Options.aimbot_fov && distTemp < bestAngleLenght)
		{
			bestAngleLenght = distTemp;
			bestTarget = aimbotTarget;
		}
	}

	return bestTarget;
}

TargetInfo Aimbot::GetTargetInfo(CEntity* entity)
{
	if (!entity)
		return TargetInfo();
	if (entity->m_isDead)
		return TargetInfo();
	if (!entity->IsPlayer())
		return TargetInfo();
	if (entity->IsAlly())
		return TargetInfo();
	if (!entity->m_playerBase)
		return TargetInfo();

	Vector3 entityVelocity = entity->m_velocity;
	Vector3 aimPrediction = entity->m_playerBase->m_position;
	if (entity->IsMax())
	{
		float playerHeight = PLAYER_HEIGHT * GetHeightFactor(entity);
		aimPrediction.y += playerHeight;
	}
	else
		aimPrediction += entity->GetBonePosition(Bone::head);

	float distance = CGameInstance::GetFirstObject()->m_playerBase->m_position.DistTo(aimPrediction);
	float timeToHit = distance / 550.f;
	if (distance < 20)
		aimPrediction += entityVelocity * 0.05f;
	else
		aimPrediction += entityVelocity * timeToHit;
	// Bullet drop
	if (distance > 49)
	{
		float bulletDrop = (0.001f * distance);
		aimPrediction.y += bulletDrop;
	}

	Vector3 toHead;
	TargetInfo targetInfo;
	if (CGraphicsInstance::WorldToScreen(&toHead, aimPrediction))
	{
		targetInfo.screenPosition = toHead;
		targetInfo.entity = entity;
		targetInfo.isInScreen = true;
	}
	else
	{
		targetInfo.entity = nullptr;
		targetInfo.screenPosition = Vector3(0, 0, 0);
		targetInfo.isInScreen = false;
	}
	return targetInfo;
}

void Aimbot::OnUpdate(int)
{
	if (!isLock && !GetAsyncKeyState(VK_RBUTTON))
	{
		CurrentTarget = TargetInfo();
		return;
	}

	if (GetAsyncKeyState(VK_MBUTTON))
	{
		isLock = !isLock;
		Sleep(300);
	}

	CEntity* localPlayer = CGameInstance::GetFirstObject();
	if (!localPlayer)
		return;

	if (!CurrentTarget.isInScreen)
	{
		CurrentTarget = GetBestTarget();
	}

	CurrentTarget = GetTargetInfo(CurrentTarget.entity);
	if (CurrentTarget.isInScreen)
	{
		InputSys::Get().MoveMouse((int)CurrentTarget.screenPosition.x - SCREEN_WIDTH / 2, (int)CurrentTarget.screenPosition.y - SCREEN_HEIGHT / 2);
	}
}

void Aimbot::Initialize()
{
	EventHandler<EventIndex::OnUpdate, EventDefines::OnUpdate, int>::GetInstance()->Add(Aimbot::OnUpdate);
}
