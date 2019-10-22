#include "stdafx.h"
#include "Inputs.h"

//#include "Menu.h"

#include <iostream>

//extern LRESULT ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

InputSys::InputSys()
{
	m_hTargetWindow = nullptr;
	m_originalWndProc = 0;
}

InputSys::~InputSys()
{
	if (m_originalWndProc)
		SetWindowLongPtr(m_hTargetWindow, GWLP_WNDPROC, m_originalWndProc);
	m_originalWndProc = 0;
}

void InputSys::Initialize(HWND hTargetWindow)
{
	//m_hTargetWindow = FindWindow(NULL, "Planetside2 v1.0.1022.394444 x64");
	m_hTargetWindow = hTargetWindow;
	TCHAR className[256];
	GetClassName(m_hTargetWindow, className, 256);
	std::cout << "Class Name is : " << className << std::endl;

	printf("[Inputs] m_hTargetWindow = %p\n", m_hTargetWindow);
	if (!m_hTargetWindow)
	{
		std::cout << "[Inputs] [ERROR] m_hTargetWindow failed\n";
		return;
	}

	m_originalWndProc = SetWindowLongPtr(m_hTargetWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

	if (m_originalWndProc)
		std::cout << "[Inputs] [SUCCES]\n";
	else
		std::cout << "[Inputs] [FAILED]\n";
}

void InputSys::Shutdown()
{
	if (m_originalWndProc)
		SetWindowLongPtr(m_hTargetWindow, GWLP_WNDPROC, m_originalWndProc);
	m_originalWndProc = 0;
}

LRESULT __stdcall InputSys::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Get().ProcessMessage(msg, wParam, lParam);

	//if (Menu::IsVisible()) {
	//	ImGui_ImplDX9_WndProcHandler(hWnd, msg, wParam, lParam);
	//}
	//ImGui_ImplDX11_WndProcHandler(hWnd, msg, wParam, lParam);
	return CallWindowProcW((WNDPROC)Get().m_originalWndProc, hWnd, msg, wParam, lParam);
}

bool InputSys::ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
	case WM_LBUTTONDBLCLK:
	case WM_XBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_XBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
	case WM_LBUTTONUP:
	case WM_XBUTTONUP:
		return ProcessMouseMessage(uMsg, wParam, lParam);
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return ProcessKeybdMessage(uMsg, wParam, lParam);
	default:
		return false;
	}
}

bool InputSys::ProcessMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto key = VK_LBUTTON;
	auto state = KeyState::None;
	switch (uMsg) {
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		state = uMsg == WM_MBUTTONUP ? KeyState::Up : KeyState::Down;
		key = VK_MBUTTON;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		state = uMsg == WM_RBUTTONUP ? KeyState::Up : KeyState::Down;
		key = VK_RBUTTON;
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		state = uMsg == WM_LBUTTONUP ? KeyState::Up : KeyState::Down;
		key = VK_LBUTTON;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
		state = uMsg == WM_XBUTTONUP ? KeyState::Up : KeyState::Down;
		key = (HIWORD(wParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
		break;
	default:
		return false;
	}

	if (state == KeyState::Up && m_iKeyMap[key] == KeyState::Down)
		m_iKeyMap[key] = KeyState::Pressed;
	else
		m_iKeyMap[key] = state;
	return true;
}

bool InputSys::ProcessKeybdMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto key = wParam;
	auto state = KeyState::None;

	switch (uMsg) {
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		state = KeyState::Down;
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		state = KeyState::Up;
		break;
	default:
		return false;
	}

	if (state == KeyState::Up && m_iKeyMap[int(key)] == KeyState::Down) {
		m_iKeyMap[int(key)] = KeyState::Pressed;

		auto& hotkey_callback = m_Hotkeys[key];

		if (hotkey_callback)
			hotkey_callback();

	}
	else {
		m_iKeyMap[int(key)] = state;
	}

	return true;
}
KeyState InputSys::GetKeyState(std::uint32_t vk)
{
	return m_iKeyMap[vk];
}
bool InputSys::IsKeyDown(std::uint32_t vk)
{
	return m_iKeyMap[vk] == KeyState::Down;
}
bool InputSys::WasKeyPressed(std::uint32_t vk)
{
	if (m_iKeyMap[vk] == KeyState::Pressed) {
		m_iKeyMap[vk] = KeyState::Up;
		return true;
	}
	return false;
}

void InputSys::RegisterHotkey(std::uint32_t vk, std::function<void(void)> f)
{
	m_Hotkeys[vk] = f;
}
void InputSys::RemoveHotkey(std::uint32_t vk)
{
	m_Hotkeys[vk] = nullptr;
}

void InputSys::MoveMouse(int x, int y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dx = (LONG)x;
	Input.mi.dy = (LONG)y;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &Input, sizeof(INPUT));
}
