#pragma once
#include"../cursor/cursor.hpp"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
namespace hooks
{
	//inline Hook* pHook = nullptr;
	namespace WndProc
	{
		using Fn = LRESULT(__fastcall*)(HWND, UINT, WPARAM, LPARAM);
		LRESULT __fastcall Detour(HWND hWnd, UINT uInt, WPARAM wParam, LPARAM lParam) {
			if (pOverlay->render_overlay) {
				ImGui_ImplWin32_WndProcHandler(hWnd, uInt, wParam, lParam);
				return TRUE;
			}
			return pWinApi->CallWndProc(pD3D11->oWndProc, hWnd, uInt, wParam, lParam);
		}
		__declspec(dllexport) void Initialize() {
			pD3D11->oWndProc = reinterpret_cast<oWndProcFn>(pWinApi->NtSetWindowLongPtr(pD3D11->hWindow, GWLP_WNDPROC, reinterpret_cast<LONG>(Detour)));
		}
	}
}