//#include "CNoclip.h"
//#include "Offsets.h"
//
//DWORD64 CNoclip::m_noclipbase = 0;
//
//DWORD64 CNoclip::GetNoClipBase()
//{
//	if (!m_noclipbase)
//		SetNoClipBase();
//	return m_noclipbase;
//}
//
//bool CNoclip::SetNoClipBase()
//{
//	auto p0 = *reinterpret_cast<DWORD64*>(oNoClip);
//	if (!p0) return false;
//
//	auto p1 = *reinterpret_cast<DWORD64*>(p0 + 0x238);
//	if (!p1) return false;
//
//	auto p2 = *reinterpret_cast<DWORD64*>(p1 + 0x2E8);
//	if (!p2) return false;
//
//	auto p3 = *reinterpret_cast<DWORD64*>(p2 + 0x540);
//	if (!p3) return false;
//
//	m_noclipbase = *reinterpret_cast<DWORD64*>(p3 + 0x30);
//	return m_noclipbase;
//}
//
//Vector3 CNoclip::GetNoclipPosition()
//{
//	if (!m_noclipbase) 
//	{
//		if (!SetNoClipBase())
//			return Vector3(0, 0, 0);
//	}
//
//	return *reinterpret_cast<Vector3*>(m_noclipbase + 0x0);
//}
//
//void CNoclip::SetNoClipPosition(Vector3 position)
//{
//	if (!m_noclipbase)
//	{
//		if (!SetNoClipBase())
//			return;
//	}
//
//	auto pPosition = reinterpret_cast<Vector3*>(m_noclipbase + 0x0);
//	if (pPosition)
//		*pPosition = position;
//}