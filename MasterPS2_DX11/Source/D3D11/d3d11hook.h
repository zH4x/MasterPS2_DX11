/***
*         _ ____    _ _ _   _             _
*      __| |__ / __| / / | | |_  ___  ___| |__
*     / _` ||_ \/ _` | | | | ' \/ _ \/ _ \ / /
*     \__,_|___/\__,_|_|_| |_||_\___/\___/_\_\
*
*     D3D11Hook by Rebzzel
*	  Added ImGui + InputHook by Sh0ckFR - https://twitter.com/Sh0ckFR
*     For compile hook you need:
*      - DirectX SDK (https://www.microsoft.com/en-us/download/details.aspx?id=6812)
*      - Minhook (you can download in NuGet or github repository https://github.com/TsudaKageyu/minhook)
*     License: https://github.com/Rebzzel/Universal-D3D11-Hook#license
*/


#ifndef D3D11_HOOK_H_INCLUDED_
#define D3D11_HOOK_H_INCLUDED_

#define D3D11_HOOK_API extern

struct ID3D11Device; // from d3d11.h
struct ID3D11DeviceContext; // from d3d11.h
struct IDXGISwapChain; // from d3d11.h

namespace D3D11Hook
{
								// Use for rendering graphical user interfaces (for example: ImGui) or other.
	D3D11_HOOK_API void			PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	// Use for initialize hook.
	D3D11_HOOK_API void			Initialize(HMODULE hModule, void* hwnd);

	// Use for untialize hook (ONLY AFTER INITIALIZE).
	D3D11_HOOK_API void			Shutdown();

	D3D11_HOOK_API void			HookVirtualTable(DWORD_PTR* virtualTable, int index, PVOID detourFunction);
}


#endif
