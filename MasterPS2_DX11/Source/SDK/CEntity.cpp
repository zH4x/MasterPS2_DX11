#include "..\stdafx.h"
#include "CEntity.h"
#include "CGame.h"

bool CEntity::IsPlayer()
{
	if (!this->m_playerBase)
		return false;

	int type = (int)this->m_type;

	static int SIZE = 4;
	static int invalid_types[] = { 3, 9, 11, 18 };
	for (size_t i = 0; i < SIZE; ++i)
		if (type == invalid_types[i]) return false;

	return (type >= 2 && type <= 23) || (type >= 190 && type <= 194);
}

bool CEntity::IsVehicule()
{
	int type = (int)this->m_type;

	static int SIZE = 2;
	static int invalid_types[] = { 25, 32 };
	for (size_t i = 0; i < SIZE; ++i)
		if (type == invalid_types[i]) return false;

	return type == 95 || (type >= 24 && type <= 37);
}

bool CEntity::IsMax()
{
	Type entityType = this->m_type;

	return entityType == Type::ARMOR_NC_MAX || entityType == Type::ARMOR_TR_MAX || entityType == Type::ARMOR_VS_MAX;
}

bool CEntity::IsType(Type type)
{
	return this->m_type == type;
}

bool CEntity::IsAlly()
{
	return CGameInstance::GetFirstObject()->m_faction == this->m_faction || this->m_faction == Faction::NS;
}

void CEntity::SetGroundSpeed(float value)
{
	this->m_sprintSpeed = value;
}

Vector3 CEntity::GetBonePosition(Bone boneID, bool fixed)
{
	auto actor = this->m_actor;
	if (!actor) return Vector3(0, 0, 0);

	auto start = actor->m_skeleton;
	if (!start) return Vector3(0, 0, 0);

	auto skeleton = start->m_skeletonInfo;
	if (!skeleton) return Vector3(0, 0, 0);

	auto bone = skeleton->m_boneInfo;
	if (!bone) return Vector3(0, 0, 0);

	Vector3 bonePosition = *reinterpret_cast<Vector3*>((DWORD64)bone + 0x194 + (DWORD64)((int)boneID * 0xC));

	if (fixed)
		GetBoneFixed(bonePosition);

	return bonePosition;
}

void CEntity::GetBoneFixed(Vector3& bonePosition)
{
	D3DXVECTOR3 dxBonePosition = D3DXVECTOR3(bonePosition.x, bonePosition.y, bonePosition.z);

	D3DXMATRIX RotateY;
	float Yaw = this->m_viewAngles.x;
	D3DXMatrixRotationY(&RotateY, (Yaw + 1.6f - M_PI / 2.f));
	D3DXVECTOR3 boneFixed;
	D3DXVec3TransformCoord(&boneFixed, &dxBonePosition, &RotateY);

	bonePosition = Vector3(boneFixed.x, boneFixed.y, boneFixed.z);
}
