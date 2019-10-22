//#include "stdafx.h"
//#include "ImGui/imgui_internal.h"
//#include "Menu.h"
//
//#include "EventManager.h"
//#include "SDK/CGraphics.h"
//#include "D3D9.h"
//#include "Inputs.h"
//#include "Options.h"
//
//bool Menu::_isVisible = false;
//ImGuiStyle Menu::_style;
//
//// ImGui
//bool p_open = true;
//
//static int active_sidebar_tab = 0;
//static const char* sidebar_tabs[] = {
//	"AIMBOT",
//	"VISUALS",
//	"NO CLIP",
//	"MISC",
//};
//
//constexpr static float get_sidebar_item_width() { return 150.0f; }
//constexpr static float get_sidebar_item_height() { return  50.0f; }
//
//ImVec2 get_sidebar_size()
//{
//	constexpr float padding = 10.0f;
//	constexpr auto size_w = padding * 2.0f + get_sidebar_item_width();
//	constexpr auto size_h = padding * 2.0f + (sizeof(sidebar_tabs) / sizeof(char*)) * get_sidebar_item_height();
//
//	return ImVec2{ size_w, ImMax(325.0f, size_h) };
//}
//
//template<size_t N>
//void render_tabs(const char* (&names)[N], int& activetab, float w, float h, bool sameline)
//{
//	bool values[N] = { false };
//
//	values[activetab] = true;
//
//	for (auto i = 0u; i < N; ++i) {
//		if (ImGui::ToggleButton(names[i], &values[i], ImVec2{ w, h })) {
//			activetab = i;
//		}
//		if (sameline && i < N - 1)
//			ImGui::SameLine();
//	}
//}
//
//void RenderAimbotTab()
//{
//	bool placeholder_true = true;
//
//	auto& style = ImGui::GetStyle();
//	float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
//	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
//
//	// Render
//	ImGui::Columns(2, nullptr, false);
//	ImGui::SetColumnOffset(1, group_w / 2.0f);
//	ImGui::SetColumnOffset(2, group_w);
//
//	ImGui::Checkbox("Enable Aimbot", &g_Options.aimbot);
//	ImGui::Text("Hold Right Mouse Button");
//	ImGui::Checkbox("Aim to Head", &g_Options.aimbot_aimtohead);
//	ImGui::Checkbox("Screen Range Circle", &g_Options.aimbot_circlerange);
//	ImGui::SliderInt("FOV", &g_Options.aimbot_fov, 50, 400);
//	if (ImGui::Button("Default")) { g_Options.aimbot_fov = 150; }
//
//	ImGui::NextColumn();
//
//	ImGui::PopStyleVar();
//}
//
//void RenderVisualTab()
//{
//	bool placeholder_true = true;
//
//	auto& style = ImGui::GetStyle();
//	float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
//	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
//
//	// Render
//	ImGui::Columns(2, nullptr, false);
//	ImGui::SetColumnOffset(1, group_w / 3.0f);
//	ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
//
//	ImGui::Checkbox("Enable Visuals", &g_Options.visuals);
//	ImGui::Checkbox("ESP Boxes", &g_Options.visuals_box);
//	ImGui::Checkbox("Snap Lines", &g_Options.visuals_snaplines);
//	ImGui::Checkbox("Distance", &g_Options.visuals_showdistance);
//	ImGui::Checkbox("Name", &g_Options.visuals_showname);
//
//	ImGui::Text("Filter :");
//	ImGui::Checkbox("Show Allies", &g_Options.visuals_showallies);
//	ImGui::Checkbox("Show Vehicules", &g_Options.visuals_showvehicules);
//
//	ImGui::NextColumn();
//	ImGui::Checkbox("No Tree Leaves", &g_Options.visuals_notreeleaves);
//
//	ImGui::PopStyleVar();
//}
//
//void RenderMiscTab()
//{
//	bool placeholder_true = true;
//
//	auto& style = ImGui::GetStyle();
//	float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
//	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
//
//	// Render
//	ImGui::Columns(2, nullptr, false);
//	ImGui::SetColumnOffset(1, group_w / 3.0f);
//	ImGui::SetColumnOffset(2, 2 * group_w / 3.0f);
//
//	ImGui::Checkbox("Speed Hack", &g_Options.speedhack);
//	ImGui::SliderInt("Velocity", &g_Options.speedhack_velocity, 1, 25);
//	if (ImGui::Button("Default")) { g_Options.speedhack_velocity = 9; }
//
//	ImGui::NextColumn();
//	ImGui::Checkbox("Super JetPack", &g_Options.jetpack);
//	ImGui::SliderInt("JetPack Speed", &g_Options.jetpack_velocity, 10, 1000);
//	if (ImGui::Button("Default")) { g_Options.jetpack_velocity = 310; }
//
//	ImGui::PopStyleVar();
//}
//
//const char* NoClipSpeedItems[] = { "Slow", "Normal", "Fast", "VeryFast", "Insane" };
//void RenderNoClipTab()
//{
//	bool placeholder_true = true;
//	auto& style = ImGui::GetStyle();
//	float group_w = ImGui::GetCurrentWindow()->Size.x - style.WindowPadding.x * 2;
//	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ style.WindowPadding.x, style.ItemSpacing.y });
//
//	// Render
//	ImGui::Columns(2, nullptr, false);
//	ImGui::SetColumnOffset(1, group_w / 2.0f);
//	ImGui::SetColumnOffset(2, 2 * group_w / 2.0f);
//
//	ImGui::Checkbox("Noclip Hack", &g_Options.noclip);
//	ImGui::Combo("Speed", &g_Options.noclip_speed, NoClipSpeedItems, 5);
//	if (ImGui::Button("Default")) { g_Options.noclip_speed = 1; }
//	ImGui::Text("Toggle Key is : VK_OEM_3 (next to '1' and 'tab')");
//	ImGui::PopStyleVar();
//}
//
//void Menu::OnPresent(LPDIRECT3DDEVICE9 device)
//{
//	if (!Menu::IsVisible())
//		return;
//
//	ImGui_ImplDX11_NewFrame();
//
//	ImGui::PushStyle(_style);
//	ImGui::SetNextWindowPos(ImVec2{ 0, 0 }, ImGuiSetCond_Once);
//	ImGui::SetNextWindowSize(ImVec2{ 800, 0 }, ImGuiSetCond_Once);
//
//	const auto sidebar_size = get_sidebar_size();
//	static int active_sidebar_tab = 0;
//
//	ImGui::Begin("MasterPS2", &Menu::_isVisible,
//		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize);
//
//	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
//	{
//		ImGui::BeginGroupBox("##sidebar", sidebar_size);
//		{
//			//ImGui::GetCurrentContext()->Flags &= ~ImGuiWindowFlags_ShowBorders;
//
//			render_tabs(sidebar_tabs, active_sidebar_tab, get_sidebar_item_width(), get_sidebar_item_height(), false);
//		}
//		ImGui::EndGroupBox();
//	}
//	ImGui::PopStyleVar();
//	ImGui::SameLine();
//
//	auto size = ImVec2{ 0.0f, sidebar_size.y };
//	ImGui::BeginGroupBox("##body", size);
//	if (active_sidebar_tab == 0) {
//		RenderAimbotTab();
//	}
//	else if (active_sidebar_tab == 1) {
//		RenderVisualTab();
//	}
//	else if (active_sidebar_tab == 2) {
//		RenderNoClipTab();
//	}
//	else if (active_sidebar_tab == 3) {
//		RenderMiscTab();
//	}
//	ImGui::EndGroupBox();
//	ImGui::End();
//	ImGui::Render();
//}
//
//void Menu::Initialize()
//{
//	_isVisible = true;
//
//	ImGuiIO& io = ImGui::GetIO();
//	io.DeltaTime = 1.f / 60.f;
//	//ImGui_ImplDX11_Init(InputSys::Get().GetMainWindow(), CGraphicsInstance::GetDevice());
//	CreateStyle();
//
//	EventHandler<EventIndex::OnDrawingPresent, EventDefines::OnDrawingPresent, IDXGISwapChain *, UINT, UINT>::GetInstance()->Add(Menu::OnPresent);
//	//EventHandler<EventIndex::OnReset, EventDefines::OnReset, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*>::GetInstance()->Add(Menu::OnReset);
//}
//
//void Menu::Shutdown()
//{
//	ImGui_ImplDX11_Shutdown();
//}
//
//void Menu::CreateStyle()
//{
//
//	_style.Alpha = 1.0f;                                // Global alpha applies to everything in ImGui
//	_style.WindowPadding = ImVec2(10, 10);                      // Padding within a window
//	_style.WindowMinSize = ImVec2(100, 100);                    // Minimum window size
//	_style.WindowRounding = 0.0f;                                // Radius of window corners rounding. Set to 0.0f to have rectangular windows
//	_style.WindowTitleAlign = ImVec2(0.0f, 0.5f);                  // Alignment for title bar text
//	_style.ChildWindowRounding = 0.0f;                                // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
//	_style.FramePadding = ImVec2(5, 5);                        // Padding within a framed rectangle (used by most widgets)
//	_style.FrameRounding = 0.0f;                                // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
//	_style.ItemSpacing = ImVec2(5, 5);                        // Horizontal and vertical spacing between widgets/lines
//	_style.ItemInnerSpacing = ImVec2(4, 4);                        // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
//	_style.TouchExtraPadding = ImVec2(0, 0);                        // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
//	_style.IndentSpacing = 21.0f;                               // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
//	_style.ColumnsMinSpacing = 6.0f;                                // Minimum horizontal spacing between two columns
//	_style.ScrollbarSize = 16.0f;                               // Width of the vertical scrollbar, Height of the horizontal scrollbar
//	_style.ScrollbarRounding = 9.0f;                                // Radius of grab corners rounding for scrollbar
//	_style.GrabMinSize = 10.0f;                               // Minimum width/height of a grab box for slider/scrollbar
//	_style.GrabRounding = 0.0f;                                // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
//	_style.ButtonTextAlign = ImVec2(0.5f, 0.5f);                  // Alignment of button text when button is larger than text.
//	_style.DisplayWindowPadding = ImVec2(22, 22);                      // Window positions are clamped to be IsVisible within the display area by at least this amount. Only covers regular windows.
//	_style.DisplaySafeAreaPadding = ImVec2(4, 4);                        // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
//	_style.AntiAliasedLines = true;                                // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
//	_style.AntiAliasedShapes = true;                                // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
//	_style.CurveTessellationTol = 1.25f;                               // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
//
//	_style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
//	_style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
//	_style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
//	_style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
//	_style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.00f);
//	_style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
//	_style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
//	_style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//	_style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
//	_style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
//	_style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
//	_style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
//	_style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
//	_style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
//	//_style.Colors[ImGuiCol_TitleText] = ImVec4(0.80f, 0.80f, 1.00f, 1.00f);
//	_style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
//	_style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
//	_style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
//	_style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
//	_style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 0.40f);
//	_style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
//	_style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.60f, 0.90f, 0.50f);
//	_style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
//	_style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
//	_style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
//	_style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.40f, 0.00f, 0.00f, 1.00f);
//	_style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.20f, 0.00f, 0.83f);
//	_style.Colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
//	_style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
//	_style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
//	_style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
//	_style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
//	_style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
//	_style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
//	_style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
//	_style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
//	_style.Colors[ImGuiCol_CloseButton] = ImVec4(0.10f, 0.10f, 0.10f, 0.50f);
//	_style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.00f, 0.00f, 1.00f);
//	_style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.20f, 0.00f, 0.83f);
//	_style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
//	_style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
//	_style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
//	_style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
//	_style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
//}