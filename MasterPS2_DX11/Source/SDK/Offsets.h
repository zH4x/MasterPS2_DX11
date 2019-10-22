#pragma once
#define oCGame					0x143B1EC58 // CGame : 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B F8 48 85 C0 74 2D (disassemble -> mov ...)
#define oCD3D11Wrapper			(oCGame - 0x620)	// SwapChain base address : CGame - 0x50
#define oGroundSpeed			0x14399A860

class Offsets
{
public:

	enum class CGame
	{
		Graphics	= 0x2538,
		FirstObject = 0x2548
	};

	enum class CGraphics
	{
		GraphicDllWrapper = 0x50
	};

	////////////////////--GAMEOBJECTS--/////////////////////////

	enum class CEntity
	{
		Faction = 0x0208,
		pNextObject = 0x0368,
		Velocity = 0x1320,
		Name = 0x1A18,
		Description = 0x1B14,
		ShortDescription = 0x1968, //Male = player
		Stance = 0x22A0,
		IsDead = 0x2368,
		Position = 0x12F0, //0x2390
		JetpackVelocity = 0x2410,
		Yaw = 0x2580, //0x1310
		Pitch = Yaw + 0x4
	};
};


