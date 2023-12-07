#pragma once
#include"dx11/dx11.hpp"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_dx11.h"
#include"imgui/imgui_impl_win32.h"
#include"../../sdk/utils/utils.hpp"
#include "fonts/icons_data.hpp"
#include "../vars/vars.hpp"

ImVec4 Hex(int hexValue, float alpha)
{
	float r = (hexValue >> 16) & 0xFF;
	float g = (hexValue >> 8) & 0xFF;
	float b = hexValue & 0xFF;

	return ImVec4(r / 255, g / 255, b / 255, alpha);
}

class OverlayGlobals {
public:
	bool render_overlay = false;
	bool init_imgui = false;
public:
	unsigned long window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
	bool close_button = false;
public:
	enum class MenuTabs {
		Visuals,
		Misc
	};
	MenuTabs CurrentTab = MenuTabs::Visuals;
};

class CFonts {
public:
	ImFont* VerdanaSmall = nullptr;
	ImFont* TitleFont = nullptr;
	ImFont* IconFont = nullptr;
	ImFont* GameFont = nullptr;
public:
	__declspec(dllexport) void InitFonts() {
		{
			const auto& io = ImGui::GetIO();
			auto fontConfig = ImFontConfig();
			fontConfig.OversampleH = 2;
			constexpr ImWchar fontRange[]{ 0x0020, 0x00FF,0x0400, 0x044F, 0 };
			this->VerdanaSmall = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 12.0f, &fontConfig, fontRange);
			this->TitleFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdanab.ttf", 20.0f, &fontConfig, fontRange);

			constexpr ImWchar iconRange[]{ ICON_MIN_MD, ICON_MAX_MD, 0 };
			ImFontConfig iconConfig;
			iconConfig.MergeMode = true;
			iconConfig.PixelSnapH = true;
			IconFont = io.Fonts->AddFontFromMemoryCompressedTTF(MaterialFont_compressed_data, MaterialFont_compressed_size, 12.f, &iconConfig, iconRange);

			GameFont = ImGui::GetIO().Fonts->AddFontDefault();

			io.Fonts->Build(); 
		}
	}
};

class CImGui : public CFonts {
public:
	__declspec(dllexport) void InitImGui() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplDX11_Init(pD3D11->pDevice, pD3D11->pDeviceContext);
		ImGui_ImplWin32_Init(pD3D11->hWindow);
	}
	__declspec(dllexport) void InitStyle() {
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::StyleColorsDark();

		style.WindowRounding = 4;
		style.ChildRounding = 4;
		style.FrameRounding = 3;
		style.PopupRounding = 3;
		style.GrabRounding = 3;
		style.TabRounding = 3;
		style.ScrollbarRounding = 3;
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.FramePadding = { 6.0f, 6.0f };
		style.ItemSpacing = { 9.0f, 9.0f };
		style.WindowPadding = { 9.0f, 9.0f };
		style.ItemInnerSpacing = { 8.0f, 4.0f };
		style.WindowBorderSize = 1;
		style.FrameBorderSize = 1;
		style.ScrollbarSize = 12.f;
		style.GrabMinSize = 8.f;
		//style.WindowShadowSize = 0.f;

		//style.Colors[ImGuiCol_WindowShadow] = Hex(0xDB4141, 1.0f); // 0x5E61BA

		style.Colors[ImGuiCol_WindowBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_ChildBg] = Hex(0x151515, 1.0f);
		style.Colors[ImGuiCol_MenuBarBg] = Hex(0x191919, 1.0f);

		style.Colors[ImGuiCol_TitleBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = Hex(0x111111, 1.0f);

		style.Colors[ImGuiCol_Border] = Hex(0x1F1F1F, 1.0f);
		style.Colors[ImGuiCol_Separator] = Hex(0x1F1F1F, 1.0f);

		style.Colors[ImGuiCol_SliderGrab] = Hex(0x5500ffd9, 1.0f);
		style.Colors[ImGuiCol_SliderGrabActive] = Hex(0x5500ffd9, 0.8f);

		style.Colors[ImGuiCol_CheckMark] = Hex(0xE8E8E8, 1.0f);
		style.Colors[ImGuiCol_Text] = Hex(0xE8E8E8, 1.0f);
		style.Colors[ImGuiCol_TextDisabled] = Hex(0x616161, 1.0f);

		style.Colors[ImGuiCol_Header] = Hex(0x212121, 1.0f);
		style.Colors[ImGuiCol_HeaderHovered] = Hex(0x444444, 1.0f);
		style.Colors[ImGuiCol_HeaderActive] = Hex(0x363636, 1.0f);

		style.Colors[ImGuiCol_FrameBg] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = Hex(0x111111, 0.9f);
		style.Colors[ImGuiCol_FrameBgActive] = Hex(0x111111, 0.8f);

		style.Colors[ImGuiCol_Button] = Hex(0x111111, 1.0f);
		style.Colors[ImGuiCol_ButtonHovered] = Hex(0x111111, 0.8f);
		style.Colors[ImGuiCol_ButtonActive] = Hex(0x111111, 0.6f);

		style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(0, 0, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(0, 0, 0, 0);
	}

public:
	__declspec(dllexport) void Initialize() {
		this->InitImGui();
		this->InitStyle();
		this->InitFonts();
	}
}; CImGui* pImGui = new CImGui();

class Tabs {
public:
	__declspec(dllexport) void visuals_tab() {}
	__declspec(dllexport) void misc_tab()
	{
		

	}
}; Tabs* pTabs = new Tabs();

class Overlay : public OverlayGlobals {
public:
	__declspec(dllexport) void Tabs(MenuTabs Tab) {
		switch (Tab) {
			case MenuTabs::Visuals:
				break;
			case MenuTabs::Misc:
				pTabs->misc_tab();
				break;
		}
	}
	__declspec(dllexport) void Menu() {

		int height = 40;
		int width = 100;

		ImGui::Columns(2);
		ImGui::SetColumnOffset(1, width + 30);

		static MenuTabs Tab = MenuTabs::Visuals;
		{
			static ImVec4 InActive = ImVec4(0.09f, 0.09, 0.09f, 0.88f);
			static ImVec4 Active = ImVec4(0.0f, 0.5f, 0.5f, 0.9f);

			ImGui::Spacing();
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.f);
			ImGui::PushFont(pImGui->IconFont);

			ImGui::PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Visuals ? Active : InActive);
			if (ImGui::Button(Utils::add_strings(ICON_MD_BRUSH, " Visuals").c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Visuals;

			ImGui::Spacing();
			ImGui::PushStyleColor(ImGuiCol_Button, Tab == MenuTabs::Misc ? Active : InActive);
			if (ImGui::Button(Utils::add_strings(ICON_MD_KEYBOARD, " Misc  ").c_str(), ImVec2(width, height)))
				Tab = MenuTabs::Misc;

			ImGui::PopFont();
			ImGui::PopStyleColor(2);
			ImGui::PopStyleVar(1);
		}

		ImGui::NextColumn();
		{
			this->Tabs(Tab);
		}
	}
	__declspec(dllexport) void render_background(float w, float h, float x, float y, ImColor color)
	{
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2{ w, h }, ImVec2(x, y), color);
	}
public:
	__declspec(dllexport) void RenderImGui(const char* wnd_title) {
		this->render_background(0, 0, ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y, { 15,15,15,200 });
		ImGui::Begin(wnd_title, &this->close_button, this->window_flags);

		ImGui::SetWindowSize(ImVec2(795, 425));
		this->Menu();
		
		ImGui::End();
	}
}; Overlay* pOverlay = new Overlay();