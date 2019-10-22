#include "..\stdafx.h"
#include "ESP.h"

#include "..\Renderer.h"
#include "..\EventManager.h"

#include "..\SDK\CGame.h"
#include "..\SDK\CEntity.h"


#define VS_COLOR D3DCOLOR_ARGB(255, 179, 34, 255)
#define NC_COLOR D3DCOLOR_ARGB(255, 68, 132, 255)
#define TR_COLOR D3DCOLOR_ARGB(255, 255, 26, 26)

void ESP::OnRendering(int)
{
	if (!g_Options.visuals)
		return;

	CEntity* firstObject = CGameInstance::GetFirstObject();
	if (!firstObject || !firstObject->m_playerBase)
		return;

	for (auto entity : CGameInstance::GetEntities())
	{
		if (g_Options.visuals_showplayers && entity->IsPlayer())
			DrawPlayer(entity);

		//if (g_Options.visuals_showvehicules && entity->IsVehicule())
		//	DrawVehicule(entity);
	}
}

void ESP::Initialize()
{
	EventHandler<EventIndex::OnRendering, EventDefines::OnRendering, int>::GetInstance()->Add(ESP::OnRendering);
}

void ESP::DrawPlayer(CEntity* entity)
{
	CEntity* localPlayer = CGameInstance::GetFirstObject();
	if (!entity->m_playerBase)
		return;

	Vector3 feetPosition = entity->m_playerBase->m_position;

	Vector3 screenFeetPos, screenHeadPos;
	bool canSeeFeet = CGraphicsInstance::WorldToScreen(&screenFeetPos, feetPosition);
	bool canSeeHead = CGraphicsInstance::WorldToScreen(&screenHeadPos, feetPosition + Vector3(0, PLAYER_HEIGHT, 0));
	if (canSeeFeet || canSeeHead)
	{
		float height = std::abs(screenHeadPos.y - screenFeetPos.y);
		float width = height * 0.5f;
		bool ally = entity->IsAlly();

		if (g_Options.visuals_box)
		{
			D3DCOLOR factionColor = BlackColor(255);
			switch (entity->m_faction)
			{
			case Faction::VS: factionColor = VS_COLOR; break;
			case Faction::NC: factionColor = NC_COLOR; break;
			case Faction::TR: factionColor = TR_COLOR; break;
			case Faction::NS: factionColor = WhiteColor(255); break;
			}

			ImVec2 from = ImVec2(screenHeadPos.x - width / 2, screenHeadPos.y);
			ImVec2 to = ImVec2(screenFeetPos.x + width / 2, screenFeetPos.y);;

			if (g_Options.visuals_showallies && ally)
				Renderer::Get().RenderRect(from, to, factionColor);
			else if (!ally)
				Renderer::Get().RenderRect(from, to, factionColor);
		}

		if (g_Options.visuals_snaplines && !ally)
		{
			Renderer::Get().RenderLine(ImVec2(1920 / 2, 1080), ImVec2(screenFeetPos.x, screenFeetPos.y), WhiteColor(40));
		}

		//if (g_Options.visuals_showdistance && !ally)
		//{
		//	int distance = localPlayer->m_playerBase->GetServerPosition().DistTo(feetPosition);
		//	char distanceBuffer[50];
		//	sprintf_s(distanceBuffer, "[%d]", distance);
		//	CDraw::Text((int)screenFeetPos.x, (int)screenFeetPos.y, distanceBuffer, WhiteColor(100), false, false, TextAlignment::kCenter);
		//}

		//if (g_Options.visuals_showname && !ally)
		//{
		//	char* name = entity->m_name;
		//	char nameBuffer[50];
		//	sprintf_s(nameBuffer, "[%s]", name);
		//	CDraw::Text((int)screenFeetPos.x, (int)screenFeetPos.y + 16, nameBuffer, WhiteColor(100), false, false, TextAlignment::kCenter);
		//}
	}
}
