#include "CGame.h"
#include "CEntity.h"
#include "Offsets.h"

CGame* CGameInstance::m_gameInstance = nullptr;

CGame* CGameInstance::Get()
{
	if (!m_gameInstance)
		m_gameInstance = *reinterpret_cast<CGame**>(oCGame);

	return m_gameInstance;
}

CEntity * CGameInstance::GetFirstObject()
{
	if (!m_gameInstance)
		m_gameInstance = *reinterpret_cast<CGame**>(oCGame);

	return m_gameInstance->m_localPlayer;
}

CGraphics* CGameInstance::GetGraphics()
{
	CGame* game = CGameInstance::Get();

	return game ? game->m_graphics : nullptr;
}

std::vector<CEntity*> CGameInstance::GetEntities()
{
	std::vector<CEntity*> allEntities;
	CEntity* localPlayer = CGameInstance::GetFirstObject();
	if (!localPlayer)
		return allEntities;

	for (CEntity* entity = localPlayer->m_nextObject; entity != nullptr; entity = entity->m_nextObject)
	{
		if (entity->m_isDead)
			continue;
		if (entity->IsPlayer() || entity->IsVehicule())
			allEntities.push_back(entity);
	}
	return allEntities;
}
