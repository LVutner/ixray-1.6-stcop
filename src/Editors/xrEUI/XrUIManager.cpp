#include "stdafx.h"
#include "../../xrEngine/stdafx.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_sdl3.h"
#include "spectrum.h"
#include <SDL3/SDL.h>

XrUIManager::XrUIManager()
{
}

XrUIManager::~XrUIManager()
{
}

static void LoadImGuiFont(ImFont*& FontHandle, const char* Font)
{
	string_path FullPath;
	FS.update_path(FullPath, _game_fonts_, Font);
	ImFontConfig FontConfig = {};
	FontConfig.OversampleH = 3;

	if (FS.exist(FullPath))
	{
		FontHandle = ImGui::GetIO().Fonts->AddFontFromFileTTF(Platform::ANSI_TO_UTF8(FullPath).c_str(), 14.0f, &FontConfig, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		R_ASSERT(FontHandle);
	}
}

namespace ImGui
{
	XREUI_API ImFont* LightFont = nullptr;
	XREUI_API ImFont* RegularFont = nullptr;
	XREUI_API ImFont* MediumFont = nullptr;
	XREUI_API ImFont* BoldFont = nullptr;
}

void embraceTheDarkness()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(8.00f, 8.00f);
	style.FramePadding = ImVec2(5.00f, 2.00f);
	style.CellPadding = ImVec2(6.00f, 6.00f);
	style.ItemSpacing = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = 1;
	style.TabBorderSize = 1;
	style.WindowRounding = 7;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.LogSliderDeadzone = 4;
	style.TabRounding = 4;
}

void XrUIManager::Initialize(HWND hWnd, IDirect3DDevice9* device, const char* ini_path)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
	ImGuiIO& io = ImGui::GetIO();
	xr_strcpy(m_name_ini, ini_path);
	io.IniFilename = m_name_ini;
	io.ConfigWindowsMoveFromTitleBarOnly = true;
#if 0
	ImGuiStyle& Style = ImGui::GetStyle();
	Style.WindowPadding.x = 8;
	Style.WindowPadding.y = 8;
	Style.FramePadding.x = 5;
	Style.FramePadding.y = 5;
	Style.CellPadding.x = 2;
	Style.CellPadding.y = 2;
	Style.ItemSpacing.x = 8;
	Style.ItemSpacing.y = 4;
	Style.ItemInnerSpacing.x = 6;
	Style.ItemInnerSpacing.y = 6;
	Style.ScrollbarSize = 16;
	Style.GrabMinSize = 16;
	Style.FrameRounding = 2;
	Style.PopupRounding = 2;
	Style.ScrollbarRounding = 2;
	Style.GrabRounding = 2;
	Style.TabRounding = 2;

	ImVec4* colors = Style.Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.16f, 0.16f, 0.18f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.05f, 0.05f, 0.05f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.27f, 0.27f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.83f, 0.83f, 0.83f, 0.54f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.75f, 0.75f, 0.75f, 0.54f);
	colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.25f, 0.54f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.54f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.25f, 0.25f, 0.54f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.54f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.75f, 0.74f, 0.74f, 0.54f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.25f, 0.25f, 0.25f, 0.54f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.75f, 0.74f, 0.74f, 0.54f);
	colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.54f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.46f, 0.46f, 0.46f, 0.54f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.46f, 0.46f, 0.46f, 0.54f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
#else
	embraceTheDarkness();
#endif
	LoadImGuiFont(ImGui::RegularFont, "RobotoMono.ttf");
	LoadImGuiFont(ImGui::LightFont, "RobotoMono-Light.ttf");
	LoadImGuiFont(ImGui::MediumFont, "RobotoMono-Medium.ttf");
	LoadImGuiFont(ImGui::BoldFont, "RobotoMono-Bold.ttf");
	
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.Fonts->Build();
	//ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplSDL3_InitForD3D(g_AppInfo.Window);
	ImGui_ImplDX9_Init(device);
}

void XrUIManager::Destroy()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

bool XrUIManager::ProcessEvent(void* Event)
{
	if (!ImGui_ImplSDL3_ProcessEvent((SDL_Event*)Event))
		return false;

	return true;
}

void XrUIManager::BeginFrame()
{
	ImGui_ImplSDL3_NewFrame();
	ImGui_ImplDX9_NewFrame();
}

void XrUIManager::EndFrame()
{
	ImGui::GetForegroundDrawList()->AddCircle({ 66, 56 }, 55, 512351, 4);
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	for (size_t i = m_UIArray.size(); i > 0; i--)
	{
		if (m_UIArray[i - 1]->IsClosed())
		{
			if (!m_UIArray[i - 1]->Flags.test(XrUI::F_NoDelete))
			{
				xr_delete(m_UIArray[i - 1]);
			}
			m_UIArray.erase(m_UIArray.begin() + (i - 1));
			i = m_UIArray.size();
			if (i == 0)return;
		}
	}
}

void XrUIManager::ResetBegin()
{
	ImGui_ImplDX9_Shutdown();
}

void XrUIManager::ResetEnd(void* NewDevice)
{
	ImGui_ImplDX9_Init((IDirect3DDevice9*)NewDevice);
}


void XrUIManager::OnDrawUI()
{
}

void XrUIManager::ApplyShortCutInput(DWORD Key)
{
	if ((ImGui::GetIO().WantTextInput))return;
	bool IsFail = true;
	if (Key >= SDL_SCANCODE_A && Key <= SDL_SCANCODE_Z)
	{
		IsFail = false;
	}
	else if (Key >= SDL_SCANCODE_0 && Key <= SDL_SCANCODE_9)
	{
		IsFail = false;
	}
	else
	{
		switch (Key)
		{
		case SDL_SCANCODE_LEFT:
		case SDL_SCANCODE_RIGHT:
		case SDL_SCANCODE_UP:
		case SDL_SCANCODE_DOWN:
		case SDL_SCANCODE_KP_0:
		case SDL_SCANCODE_KP_1:
		case SDL_SCANCODE_KP_2:
		case SDL_SCANCODE_KP_3:
		case SDL_SCANCODE_KP_4:
		case SDL_SCANCODE_KP_5:
		case SDL_SCANCODE_KP_6:
		case SDL_SCANCODE_KP_7:
		case SDL_SCANCODE_KP_8:
		case SDL_SCANCODE_KP_9:
		case SDL_SCANCODE_F1:
		case SDL_SCANCODE_F2:
		case SDL_SCANCODE_F3:
		case SDL_SCANCODE_F4:
		case SDL_SCANCODE_F5:
		case SDL_SCANCODE_F6:
		case SDL_SCANCODE_F7:
		case SDL_SCANCODE_F8:
		case SDL_SCANCODE_F9:
		case SDL_SCANCODE_F10:
		case SDL_SCANCODE_F11:
		case SDL_SCANCODE_F12:
		case SDL_SCANCODE_DELETE:
		//case SDL_SCANCODE_ADD:
		//case SDL_SCANCODE_SUBTRACT:
		//case SDL_SCANCODE_MULTIPLY:
		//case SDL_SCANCODE_DIVIDE:
		//case SDL_SCANCODE_OEM_PLUS:
		//case SDL_SCANCODE_OEM_MINUS:
		//case SDL_SCANCODE_OEM_1:
		//case SDL_SCANCODE_OEM_COMMA:
		//case SDL_SCANCODE_OEM_PERIOD:
		//case SDL_SCANCODE_OEM_2:
		//case SDL_SCANCODE_OEM_4:
		//case SDL_SCANCODE_OEM_5:
		//case SDL_SCANCODE_OEM_6:
		//case SDL_SCANCODE_OEM_7:
		case SDL_SCANCODE_SPACE:
		case SDL_SCANCODE_CANCEL:
		case SDL_SCANCODE_RETURN:
			IsFail = false;
			break;
		default:
			break;
		}
	}
	if (IsFail)return;

	int ShiftState = ssNone;

	if (ImGui::GetIO().KeyShift)ShiftState |= ssShift;
	if (ImGui::GetIO().KeyCtrl)ShiftState |= ssCtrl;
	if (ImGui::GetIO().KeyAlt)ShiftState |= ssAlt;


	if (ImGui::IsMouseDown(ImGuiMouseButton_Left))ShiftState |= ssLeft;
	if (ImGui::IsMouseDown(ImGuiMouseButton_Right))ShiftState |= ssRight;
	ApplyShortCut(Key, ShiftState);
}

void XrUIManager::Push(XrUI* ui, bool need_deleted)
{
	m_UIArray.push_back(ui);
	ui->Flags.set(!need_deleted, XrUI::F_NoDelete);
}

void XrUIManager::PushBegin(XrUI* ui, bool need_deleted)
{
	m_UIArray.insert(m_UIArray.begin(), ui);
	ui->Flags.set(!need_deleted, XrUI::F_NoDelete);
}

void XrUIManager::Draw()
{
	//BeginFrame(); 

	ImGui::NewFrame();

	//ImGui::DockSpaceOverViewport();
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + UIToolBarSize / 2));
		ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - (UIToolBarSize / 2)));
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGuiWindowFlags window_flags = 0
			| ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, UIToolBarSize));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(3, 2));
		ImGui::Begin("MyDockspace", NULL, window_flags);
		ImGuiID dockMain = ImGui::GetID("MyDockspace");

		m_MenuBarHeight = ImGui::GetWindowBarHeight();
		// Save off menu bar height for later.

		ImGui::DockSpace(dockMain);
		ImGui::End();
		ImGui::PopStyleVar(4);

	}
	
	OnDrawUI();

	for (XrUI* ui : m_UIArray)
	{
		ui->Draw();
	}

	//ImGui::EndFrame();

	//EndFrame();
}

static bool ImGui_ImplWin32_UpdateMouseCursor()
{
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
		return false;

	ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
	if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor)
	{
		// Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
		::SetCursor(NULL);
	}
	else
	{
		// Show OS mouse cursor
		LPTSTR win32_cursor = IDC_ARROW;
		switch (imgui_cursor)
		{
		case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
		case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
		case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
		case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
		case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
		case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
		case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
		case ImGuiMouseCursor_Hand:         win32_cursor = IDC_HAND; break;
		case ImGuiMouseCursor_NotAllowed:   win32_cursor = IDC_NO; break;
		}
		::SetCursor(::LoadCursor(NULL, win32_cursor));
	}
	return true;
}
#ifndef WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif
#ifndef DBT_DEVNODES_CHANGED
#define DBT_DEVNODES_CHANGED 0x0007
#endif
//IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT XrUIManager::WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#if 0
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_WINDOW_TAKE_FOCUS:
				UI->OnAppActivate
		}

		if (!IsPlayInEditor())
		{
			if (!ImGui_ImplSDL3_ProcessEvent(&event))
				return;
		}
	}

	switch (msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		switch (wParam)
		{
		case VK_MENU:
		case VK_CONTROL:
		case VK_SHIFT:
			break;
		default:
			if(!IsPlayInEditor())   ApplyShortCut((DWORD)wParam);
			break;
		}
	default:
		break;
	}
	   // return  ImGui_ImplSDL3_ProcessEvent ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);;
#endif
	return 0;
}