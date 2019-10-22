#pragma once

#include "..\SDK\Vector3.h"

class CEntity;

struct TargetInfo
{
	TargetInfo()
	{
		this->entity = nullptr;
		this->screenPosition = Vector3(0, 0, 0);
		this->isInScreen = false;
	}

	Vector3 screenPosition;
	CEntity* entity;
	bool isInScreen;
};

class Aimbot
{
	static void OnUpdate(int);
public:
	static void Initialize();

	static TargetInfo CurrentTarget;
	static bool isLock;

	static TargetInfo GetBestTarget();
	static TargetInfo GetTargetInfo(CEntity* entity);
};


