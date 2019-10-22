#pragma once
#include "..\Options.h"

class CEntity;

class ESP
{
	static void OnRendering(int);

public:
	static void Initialize();

private:
	static void DrawPlayer(CEntity*);
	//static void DrawVehicule(CEntity*);
};



