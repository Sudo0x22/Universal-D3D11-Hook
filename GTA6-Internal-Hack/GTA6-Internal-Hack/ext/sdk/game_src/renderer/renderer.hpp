#pragma once
#include"../../hooks/hooks.hpp"

typedef struct RGBA {
	DWORD r, g, b, a;
};

class Color {
	RGBA white = { 255,255,255,255 };
	RGBA black = { 255,255,255,255 };
}; Color color;

namespace draw
{
	class Render {
	public:
		__declspec(dllexport) void render_background(float w, float h, float x, float y, ImColor color);
		__declspec(dllexport) void render_text(int x, int y, int w, int h, Color* color, int thickness);
		__declspec(dllexport) void render_health(int x, int y, int w, int h, Color* color, int thickness);
	}; Render* pRender = new Render();

	__declspec(dllexport) void Render::render_background(float w, float h, float x, float y, ImColor color) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2{ w, h }, ImVec2(x, y), color);
	}
}