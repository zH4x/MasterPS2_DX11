#pragma once
#include "Names.h"
#include "CActor.h"
#include "Vector3.h"

#define PLAYER_HEIGHT 1.52f

enum class PlayerStance
{
	Standing = 0,
	Crouch = 1,
	Walking = 2,
	Running = 3,
	Falling = 4,
	CrouchWalk = 5,
	Flying = 6,
};

enum class Type
{
	ARMOR_NC_Infiltrator = 2,
	ARMOR_NC_LightAssault = 4,
	ARMOR_NC_CombatMedic = 5,
	ARMOR_NC_Engineer = 6,
	ARMOR_NC_HeavyAssault = 7,
	ARMOR_NC_MAX = 8,

	ARMOR_TR_Infiltrator = 10,
	ARMOR_TR_LightAssault = 12,
	ARMOR_TR_CombatMedic = 13,
	ARMOR_TR_Engineer = 14,
	ARMOR_TR_HeavyAssault = 15,
	ARMOR_TR_MAX = 16,

	ARMOR_VS_Infiltrator = 17,
	ARMOR_VS_LightAssault = 19,
	ARMOR_VS_CombatMedic = 20,
	ARMOR_VS_Engineer = 21,
	ARMOR_VS_HeavyAssault = 22,
	ARMOR_VS_MAX = 23,

	ARMOR_NS_Infiltrator = 190,
	ARMOR_NS_LightAssault = 191,
	ARMOR_NS_CombatMedic = 192,
	ARMOR_NS_Engineer = 193,
	ARMOR_NS_HeavyAssault = 194,

	VEHICLE_Flash = 24,
	VEHICLE_Lightning = 26,
	VEHICLE_Sunderer = 33,
	VEHICLE_Harasser = 27,
	VEHICLE_ANT = 95,
	VEHICLE_Valkyrie = 28,
	VEHICLE_Scythe = 34,
	VEHICLE_Reaver = 36,
	VEHICLE_Mosquito = 35,
	VEHICLE_Liberator = 37,
	VEHICLE_Magrider = 29,
	VEHICLE_Prowler = 30,
	VEHICLE_Vanguard = 31,

	TURRET = 104
};

class CServerPosition
{
public:
	Vector3 m_fastPosition; //0x0000
	char pad_000C[68]; //0x000C
	Vector3 m_slowPosition; //0x0050
}; //Size: 0x0094

class CComponent
{
public:
	char pad_0000[48]; //0x0000
	class CServerPosition* m_serverPosition; //0x0030
}; //Size: 0x0048

class CPlayerBase
{
public:
	char pad_0x0000[0xE0]; //0x0000
	CComponent* m_component; //0x00E0 
	char pad_0x00E8[0x2C0]; //0x00E8
	Vector3 m_position; //0x03A8 
	char pad_0x03B4[0x3C]; //0x03B4
	Vector3 m_pelvisPosition; //0x03F0 
	char pad_0x03FC[0x40C]; //0x03FC

	inline Vector3 GetServerPosition()
	{
		if (!this->m_component)
			return Vector3(0, 0, 0);
		if (!this->m_component->m_serverPosition)
			return Vector3(0, 0, 0);

		return this->m_component->m_serverPosition->m_fastPosition;
	}
	inline void ChangeServerPosition(const Vector3& v)
	{
		if (!this->m_component)
			return;
		if (!this->m_component->m_serverPosition)
			return;

		this->m_component->m_serverPosition->m_fastPosition = v;
		this->m_component->m_serverPosition->m_slowPosition = v;

		this->m_position = v;
	}
}; //Size: 0x0860

class CEntity
{
public:
	char pad_0x0000[0x268]; //0x0000
	Faction m_faction; //0x0268 
	char pad_0x026C[0xDC]; //0x026C
	CPlayerBase* m_playerBase; //0x0348 
	char pad_0x0350[0x78]; //0x0350
	CEntity* m_nextObject; //0x03C8 
	char pad_0x03D0[0xE00]; //0x03D0
	char* m_description; //0x11D0 
	char pad_0x11D8[0x78]; //0x11D8
	Type m_type; //0x1250 
	char pad_0x1254[0x1C]; //0x1254
	Vector3 m_vehiculePosition; //0x1270 
	char pad_0x127C[0x24]; //0x127C
	Vector3 m_velocity; //0x12A0 
	char pad_0x12AC[0x64]; //0x12AC
	CActor* m_actor; //0x1310 
	char pad_0x1318[0xCC0]; //0x1318
	char* m_name; //0x1FD8 
	char pad_0x1FE0[0x170]; //0x1FE0
	PlayerStance m_stance; //0x2150 
	char pad_0x2154[0xC4]; //0x2154
	unsigned char m_isDead; //0x2218 
	char pad_0x2219[0xA7]; //0x2219
	__int32 m_jetpackVelocity; //0x22C0 
	char pad_0x22C4[0x16C]; //0x22C4
	Vector3 m_viewAngles; //0x2430 
	char pad_0x243C[0x4B4]; //0x243C
	float m_sprintSpeed; //0x28F0 
	char pad_0x28F4[0x314]; //0x28F4
	//Size: 0x3804


	bool IsPlayer();
	bool IsVehicule();
	bool IsMax();
	bool IsType(Type type);

	bool IsAlly();

	void SetGroundSpeed(float value);

	Vector3 GetBonePosition(Bone, bool fixed = true);
	void GetBoneFixed(Vector3& bonePosition);
};

