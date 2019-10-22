#pragma once
#include "..\SDK\Vector3.h"

class Noclip
{
	static void OnUpdate(int);
public:
	static void OnFastUpdate();
	static void Initialize();

	static Vector3 CurrentPosition;

private:
	static void CalculateNewPosition();
};


