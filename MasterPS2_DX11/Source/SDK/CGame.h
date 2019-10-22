#pragma once
#include "CGraphics.h"

#include <vector>
#include <Windows.h>
#include <d3d9.h>

class CEntity;

class CGame
{
public:
	char pad_0x0000[0x2538]; //0x0000
	CGraphics* m_graphics; //0x2538 
	char pad_0x2540[0x8]; //0x2540
	CEntity* m_localPlayer; //0x2548 
	char pad_0x2550[0x18]; //0x2550

};

class CGameInstance
{
public:
	static CGame* Get();

	static CEntity* GetFirstObject();
	static std::vector<CEntity*> GetEntities();

	static CGraphics* GetGraphics();

private:
	static CGame* m_gameInstance;
};


