#pragma once
#include"../../../features/menu/menu.hpp"

namespace hooks
{
	inline Hook* pHook = nullptr;
	namespace cursor
	{
		using Fn = BOOL(__fastcall*)(bool);
		BOOL __fastcall Detour(bool show);
		__declspec(dllexport) bool Initialize(LPVOID pFunc, LPVOID pDet, LPVOID* pOrig);
		__declspec(dllexport) void Uninitialize(LPVOID pFunc);
	}
}