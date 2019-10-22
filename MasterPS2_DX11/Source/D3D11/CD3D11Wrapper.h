#pragma once

namespace D3D11Hook
{
	class CDxgiWrapper
	{
	public:
		char pad_0x0000[0xD8]; //0x0000
		IDXGISwapChain* m_swapChain; //0x00D8 

	}; //Size=0x00E0

	class CD3d11Wrapper
	{
	public:
		char pad_0x0000[0x18]; //0x0000
		CDxgiWrapper* m_dxgiWrapper; //0x0018 
		char pad_0x0020[0x40]; //0x0020

	}; //Size=0x0060
}
