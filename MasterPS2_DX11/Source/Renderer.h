#pragma once
#include "Singleton.h"
#include "ImGui/imgui.h"

#define opacity(v)				(255 * v) / 100

#define RedColor(a)				D3DCOLOR_ARGB(opacity(a), 255, 0, 0)
#define GreenColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 255, 0)
#define BlueColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 0, 255)
#define YellowColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 255, 0)
#define OrangeColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 125, 0)
#define WhiteColor(a)			D3DCOLOR_ARGB(opacity(a), 255, 255, 255)
#define BlackColor(a)			D3DCOLOR_ARGB(opacity(a), 0, 0, 0)

class Renderer :
	public Singleton<Renderer>
{
	friend class Singleton<Renderer>;

protected:
	Renderer();
	~Renderer();

public:
	void Initialize();

	void BeginScene();
	void EndScene();

	float RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center = false);
	void RenderLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness = 1.0f);
	void RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f, uint32_t segments = 16);
	void RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments = 16);
	void RenderRect(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All, float thickness = 1.0f);
	void RenderRectFilled(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
	void RenderImage(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color);
	void RenderImageRounded(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);

private:
	ImFont* m_pFont;
};

#define g_sRenderer Renderer::GetInstance()

//#pragma once
//#include "ImGui\imgui.h"
//#include "ImGui\imgui_internal.h"
//#include "ImGui\imgui_impl_dx11.h"
//
//enum Colors : uint32_t
//{
//	WHITE = 0xFFffffff,
//	BLACK = 0xFF000000,
//	RED = 0xFFff0000,
//	GREEN = 0xFF80ff00,
//	BLUE = 0xFF0080ff,
//	PURPLE = 0xFFff00ff,
//	YELLOW = 0xFFffff00
//};
//
//class Renderer
//{
//public:
//	static void Initialize();
//
//	static void DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness);
//	static void DrawBox(const ImVec2& pos, const ImVec2& headPosition, uint32_t color);
//	static void DrawCircle(const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f);
//	static float DrawMessage(ImFont* pFont, const std::string& text, const ImVec2& position, float size, uint32_t color, bool center);
//
//	static ImFont*	m_defaultFont;
//	static float	m_defaultFontSize;
//
//	static int		m_width;
//	static int		m_height;
//
//private:
//
//};
