#include "CGraphics.h"
#include "CGame.h"
#include "Offsets.h"
#include <iostream>

D3DXMATRIX CGraphicsInstance::GetGameMatrix()
{
	D3DXMATRIX gameMatrix;
	D3DXMATRIX cameraMatrix = CGraphicsInstance::GetCameraMatrix();

	gameMatrix.m[0][0] = cameraMatrix.m[0][0];
	gameMatrix.m[0][1] = cameraMatrix.m[1][0];
	gameMatrix.m[0][2] = cameraMatrix.m[2][0];
	gameMatrix.m[0][3] = cameraMatrix.m[3][0];

	gameMatrix.m[1][0] = -cameraMatrix.m[0][1];
	gameMatrix.m[1][1] = -cameraMatrix.m[1][1];
	gameMatrix.m[1][2] = -cameraMatrix.m[2][1];
	gameMatrix.m[1][3] = -cameraMatrix.m[3][1];

	gameMatrix.m[2][0] = cameraMatrix.m[0][2];
	gameMatrix.m[2][1] = cameraMatrix.m[1][2];
	gameMatrix.m[2][2] = cameraMatrix.m[2][2];
	gameMatrix.m[2][3] = cameraMatrix.m[3][2];

	gameMatrix.m[3][0] = cameraMatrix.m[0][3];
	gameMatrix.m[3][1] = cameraMatrix.m[1][3];
	gameMatrix.m[3][2] = cameraMatrix.m[2][3];
	gameMatrix.m[3][3] = cameraMatrix.m[3][3];

	return gameMatrix;
}

D3DXMATRIX CGraphicsInstance::GetCameraMatrix()
{
	CGraphics* graphics = CGameInstance::GetGraphics();
	if(!graphics)
		return D3DXMATRIX();

	CCamera* camera = graphics->m_camera;
	if(!camera)
		return D3DXMATRIX();

	CCameraMatrix* cameraMatrix = camera->m_cameraMatrix;
	if (!cameraMatrix)
		return D3DXMATRIX();

	return cameraMatrix->m_viewMatrix;
}

bool CGraphicsInstance::WorldToScreen(Vector3* ScreenPos, Vector3 WorldPosition)
{
	D3DXMATRIX gameMatrix	= GetGameMatrix();
	float w					= 0.0f;

	ScreenPos->x	= gameMatrix.m[0][0] * WorldPosition.x + gameMatrix.m[0][1] * WorldPosition.y + gameMatrix.m[0][2] * WorldPosition.z + gameMatrix.m[0][3];
	ScreenPos->y	= gameMatrix.m[1][0] * WorldPosition.x + gameMatrix.m[1][1] * WorldPosition.y + gameMatrix.m[1][2] * WorldPosition.z + gameMatrix.m[1][3];
	w				= (float)(gameMatrix.m[3][0] * WorldPosition.x + gameMatrix.m[3][1] * WorldPosition.y + gameMatrix.m[3][2] * WorldPosition.z + gameMatrix.m[3][3]);

	if (w < 0.01f)
		return false;

	float invw = 1.0f / w;

	ScreenPos->x *= invw;
	ScreenPos->y *= invw;

	float width		= CGameInstance::GetGraphics()->m_width;
	float height	= CGameInstance::GetGraphics()->m_height;

	float x = width / 2.f;
	float y = height / 2.f;

	x += 0.5f * (float)ScreenPos->x * width + 0.5f;
	y -= 0.5f * (float)ScreenPos->y * height + 0.5f;

	ScreenPos->x = x;
	ScreenPos->y = y;
	ScreenPos->z = 0;
	return true;
}
