#include "..\stdafx.h"

#include "d3d11hook.h"
#include "CD3D11Wrapper.h"

#include "..\SDK\Offsets.h"
#include "..\EventManager.h"
#include "..\Renderer.h"

#include "..\ImGui\imgui.h"
#include "..\ImGui\imgui_internal.h"
#include "..\ImGui\imgui_impl_dx11.h"

#include <mutex>

namespace D3D11Hook
{
	typedef HRESULT(__stdcall* D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	static HWND                     g_hWindow = nullptr;
	static HMODULE					g_hModule = nullptr;

	static ID3D11Device*			g_pd3dDevice = nullptr;
	static ID3D11DeviceContext*		g_pd3dContext = nullptr;
	static IDXGISwapChain*			g_pSwapChain = nullptr;
	static ID3D11RenderTargetView*	g_pRenderTargetView = nullptr;

	static std::once_flag           g_isInitialized;

	D3D11PresentHook                pOriginalPresent = nullptr;

	DWORD_PTR* pSwapChainVTable = nullptr;

	D3D11_HOOK_API void PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		EventHandler<EventIndex::OnRendering, EventDefines::OnRendering, int>::GetInstance()->Trigger(NULL);

		//Renderer::Get().RenderCircle(ImVec2(500, 500), 200, Colors::PURPLE, 1);
		//Renderer::Get().RenderRect(ImVec2(0, 0), ImVec2(100, 100), Colors::WHITE);
		//Renderer::Get().RenderText("MasterPS2", ImVec2(0, 0), 16.f, Colors::WHITE, false);
	}

	HRESULT __stdcall Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		std::call_once(g_isInitialized, [&]()
			{
				if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pd3dDevice)))
				{
					pSwapChain->GetDevice(__uuidof(g_pd3dDevice), (void**)&g_pd3dDevice);
					g_pd3dDevice->GetImmediateContext(&g_pd3dContext);
				}

				ID3D11Texture2D* renderTargetTexture = nullptr;
				if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
				{
					g_pd3dDevice->CreateRenderTargetView(renderTargetTexture, NULL, &g_pRenderTargetView);
					renderTargetTexture->Release();
				}

				ImGui_ImplDX11_Init(g_hWindow, g_pd3dDevice, g_pd3dContext);
				ImGui_ImplDX11_CreateDeviceObjects();

				Renderer::Get().Initialize();
			});

		g_pd3dContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
		ImGui_ImplDX11_NewFrame();

		Renderer::Get().BeginScene();
		PresentHook(pSwapChain, SyncInterval, Flags);
		Renderer::Get().EndScene();

		// Add Menu Here
		//g_sMenu.Render();

		ImGui::Render();

		return pOriginalPresent(pSwapChain, SyncInterval, Flags);
	}

	DWORD __stdcall HookDX11_Init()
	{
		D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
		D3D_FEATURE_LEVEL obtainedLevel;
		DXGI_SWAP_CHAIN_DESC sd;
		{
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount = 1;
			sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			sd.OutputWindow = g_hWindow;
			sd.SampleDesc.Count = 1;

			//sd.Windowed = ((GetWindowLongPtr(g_hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
			sd.Windowed = true;

			sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
			sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			sd.BufferDesc.Width = 1;
			sd.BufferDesc.Height = 1;
			sd.BufferDesc.RefreshRate.Numerator = 0;
			sd.BufferDesc.RefreshRate.Denominator = 1;
		}

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, 0, levels,
			sizeof(levels) / sizeof(D3D_FEATURE_LEVEL),
			D3D11_SDK_VERSION,
			&sd,
			&g_pSwapChain,
			&g_pd3dDevice,
			&obtainedLevel,
			&g_pd3dContext
		);
		if (FAILED(hr))
		{
			printf("[D3D11Hook] : Failed to create device and swapchain.");
			return E_FAIL;
		}

		CD3d11Wrapper* d3d11Wrapper = *(CD3d11Wrapper**)(oCD3D11Wrapper);
		if (!d3d11Wrapper)
		{
			printf("[D3D11Hook] : CD3d11Wrapper* is null");
			return E_FAIL;
		}
		CDxgiWrapper* dxgiWrapper = d3d11Wrapper->m_dxgiWrapper;
		if (!d3d11Wrapper)
		{
			printf("[D3D11Hook] : CDxgiWrapper* is null");
			return E_FAIL;
		}
		IDXGISwapChain* swapChain = dxgiWrapper->m_swapChain;
		if (!swapChain)
		{
			printf("[D3D11Hook] : IDXGISwapChain* is null");
			return E_FAIL;
		}
		printf("[D3D11Hook] : Original IDXGISwapChain* = 0x%p\n", (void*)swapChain);

		g_pSwapChain = swapChain;

		pSwapChainVTable = (DWORD_PTR*)(g_pSwapChain);
		pSwapChainVTable = (DWORD_PTR*)(pSwapChainVTable[0]);

		pOriginalPresent = (D3D11PresentHook)pSwapChainVTable[8];
		printf("[D3D11Hook] : Original Present Function = 0x%p\n", (void*)pOriginalPresent);

		HookVirtualTable(pSwapChainVTable, 8, &Present);

		return S_OK;
	}

	D3D11_HOOK_API void Initialize(HMODULE hModule, void* hWindow)
	{
		g_hWindow = (HWND)hWindow;
		g_hModule = hModule;
		if (HookDX11_Init() != S_OK)
		{
			printf("[D3D11Hook] : Error in HookDX11_Init\n");
		}
	}

	D3D11_HOOK_API void Shutdown()
	{
		HookVirtualTable(pSwapChainVTable, 8, pOriginalPresent);

		g_pd3dDevice->Release();
		g_pd3dContext->Release();
		g_pSwapChain->Release();
	}

	D3D11_HOOK_API void HookVirtualTable(DWORD_PTR* virtualTable, int index, PVOID detourFunction)
	{
		DWORD flOldProtect;
		VirtualProtect(virtualTable, 64, PAGE_READWRITE, &flOldProtect);
		virtualTable[index] = (DWORD64)detourFunction;
		VirtualProtect(virtualTable, 64, flOldProtect, &flOldProtect);
	}
}
