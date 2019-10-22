#pragma once
#include <Windows.h>
#include "Vector3.h"
#include <d3dx9math.h>

#define SCREEN_WIDTH	1920
#define SCREEN_HEIGHT	1080

// FOR W2S
class CCameraMatrix
{
public:
	char pad_0x0000[0x1B0]; //0x0000
	D3DMATRIX m_viewMatrix; //0x01B0 
};

class CCamera
{
public:
	char pad_0x0000[0x30]; //0x0000
	CCameraMatrix* m_cameraMatrix; //0x0030 
};

class CGraphics
{
public:
	char pad_0x0000[0x20]; //0x0000
	__int32 m_width; //0x0020 
	__int32 m_height; //0x0024 
	char pad_0x0028[0x38]; //0x0028
	CCamera* m_camera; //0x0060

}; //Size=0x0050

class CGraphicsInstance
{
public:
	static D3DXMATRIX GetGameMatrix();
	static D3DXMATRIX GetCameraMatrix();
	static bool WorldToScreen(Vector3* ScreenPos, Vector3 WorldPosition);
private:
};



