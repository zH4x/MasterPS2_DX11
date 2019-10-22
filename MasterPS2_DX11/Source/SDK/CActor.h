#pragma once

class CBoneInfo
{
public:
	char pad_0x0000[0x560]; //0x0000

}; //Size=0x0560

class CSkeletonInfo
{
public:
	char pad_0x0000[0x28]; //0x0000
	CBoneInfo* m_boneInfo; //0x0028 

}; //Size=0x0030

class CSkeleton
{
public:
	char pad_0x0000[0x50]; //0x0000
	CSkeletonInfo* m_skeletonInfo; //0x0050 

}; //Size=0x0058

class CActor
{
public:
	char pad_0x0000[0x1D8]; //0x0000
	CSkeleton* m_skeleton; //0x01D8 

}; //Size=0x01E0

enum class Bone : int
{
	CharacterWorldSpaceTM = 0,
	Male = 1,
	worldRoot = 2,
	COG = 3,
	pelvis = 4,
	R_hip = 5,
	R_knee = 6,
	R_ankle = 7,
	R_ball = 8,
	R_toe = 9,
	L_hip = 10,
	L_knee = 11,
	L_ankle = 12,
	L_ball = 13,
	L_toe = 14,
	spineLower = 15,
	spineMiddle = 16,
	spineUpper = 17,
	L_clavicle = 18,
	L_shoulder = 19,
	L_elbow = 20,
	L_wrist = 21,
	L_middleA = 22,
	L_middleB = 23,
	L_middleC = 24,
	L_middle_end = 25,
	L_ringA = 26,
	L_ringB = 27,
	L_ringC = 28,
	L_ring_end = 29,
	L_pinkyA = 30,
	L_pinkyB = 31,
	L_pinkyC = 32,
	L_pinky_end = 33,
	L_indexA = 34,
	L_indexB = 35,
	L_indexC = 36,
	L_index_end = 37,
	L_thumbA = 38,
	L_thumbB = 39,
	L_thumbC = 40,
	L_thumb_end = 41,
	L_weapon = 42,
	L_forearm = 43,
	L_shoulderRoll = 44,
	R_clavicle = 45,
	R_shoulder = 46,
	R_shoulderRoll = 47,
	R_elbow = 48,
	R_wrist = 49,
	R_middleA = 50,
	R_middleB = 51,
	R_middleC = 52,
	R_middle_end = 53,
	R_indexA = 54,
	R_indexB = 55,
	R_indexC = 56,
	R_index_end = 57,
	R_ringA = 58,
	R_ringB = 59,
	R_ringC = 60,
	R_ring_end = 61,
	R_pinkyA = 62,
	R_pinkyB = 63,
	R_pinkyC = 64,
	R_pinky_end = 65,
	R_thumbA = 66,
	R_thumbB = 67,
	R_thumbC = 68,
	R_thumb_end = 69,
	R_weapon = 70,
	R_forearm = 71,
	neck = 72,
	head = 73,
	head_end = 74,
	trajectory = 75,
};
