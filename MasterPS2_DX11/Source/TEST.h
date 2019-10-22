#pragma once
#include "SDK/SDKInclude.h"
//#include "Menu.h"
#include <iostream>
//#include "Hook.h"

namespace TEST
{
	std::vector<CEntity*> GetEntities()
	{
		std::vector<CEntity*> allEntities;
		CEntity* localPlayer = CGameInstance::GetFirstObject();
		if (!localPlayer)
			return allEntities;

		for (CEntity* entity = localPlayer->m_nextObject; entity != nullptr; entity = entity->m_nextObject)
		{
			allEntities.push_back(entity);
		}
		return allEntities;
	}

	void test1()
	{
		std::cout << "[CGame] : " << (PDWORD64)CGameInstance::Get() << std::endl;
		std::cout << "[CGame] : found " << CGameInstance::GetEntities().size() << " entities\n";

		std::cout << "\n-----------------\n";
		std::cout << "[FirstObject] Address : " << CGameInstance::GetFirstObject() << std::endl;
		std::cout << "[FirstObject] Description : " << CGameInstance::GetFirstObject()->m_description << std::endl;
		std::cout << "[FirstObject] Name : " << CGameInstance::GetFirstObject()->m_name << std::endl;
		std::cout << "[FirstObject] Faction : " << (int)CGameInstance::GetFirstObject()->m_faction << std::endl;
		std::cout << "[FirstObject] Type : " << (int)CGameInstance::GetFirstObject()->m_type << std::endl;

		auto entities = CGameInstance::GetEntities();
		for (auto entity : entities)
		{
			Vector3 pos = entity->m_playerBase->m_position;

			std::cout << "\n-----------------\n";
			std::cout << "[NextObject] Address : " << entity << std::endl;
			std::cout << "[NextObject] Description : " << entity->m_description << std::endl;
			std::cout << "[NextObject] Name : " << entity->m_name << std::endl;
			std::cout << "[NextObject] Faction : " << (int)entity->m_faction << std::endl;
			std::cout << "[NextObject] Type : " << (int)entity->m_type << std::endl;
			printf("[NextObject] Position : ( %.2f, %.2f, %.2f )\n", pos.x, pos.y, pos.z);

			//system("pause");
		}
	}

	void testGraphics()
	{
		CGraphics* graphics = CGameInstance::GetGraphics();
		std::cout << "[CGraphics] : " << (PDWORD64)CGameInstance::GetGraphics() << std::endl;
		printf("[CGraphics] :\n\
				\tWidth = %d, Height = %d", graphics->m_width, graphics->m_height);

		std::cout << "[CCamera] : " << (PDWORD64)graphics->m_camera << std::endl;
		std::cout << "[CCameraMatrix] : " << (PDWORD64)graphics->m_camera->m_cameraMatrix << std::endl;

	}

	void testMatrix()
	{
		auto matrix = CGraphicsInstance::GetGameMatrix();
		printf("Game Matrix : \n\
				\t %.2f, %.2f, %.2f, %.2f\n\
				\t %.2f, %.2f, %.2f, %.2f\n\
				\t %.2f, %.2f, %.2f, %.2f\n\
				\t %.2f, %.2f, %.2f, %.2f\n",
			matrix._11, matrix._12, matrix._13, matrix._14,
			matrix._21, matrix._22, matrix._23, matrix._24,
			matrix._31, matrix._32, matrix._33, matrix._34,
			matrix._41, matrix._42, matrix._43, matrix._44);

		auto randomPos = CGameInstance::Get()->m_localPlayer->m_playerBase->m_position + Vector3(50, 0, 0);
		Vector3 screen;
		CGraphicsInstance::WorldToScreen(&screen, randomPos);
		printf("World : ( %.2f, %.2f, %.2f ) -> Screen : ( %.2f, %.2f )",
			randomPos.x, randomPos.y, randomPos.z,
			screen.x, screen.y);

	}
}
