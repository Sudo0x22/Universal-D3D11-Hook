#pragma once
#include"present/present.hpp"

namespace Hooks
{
	__declspec(dllexport) bool Initialize()
	{
		static bool init_hook = false;
		while (!init_hook)
		{
			if (pDX11->initialize() == true) 
			{
				hooks::present::Initialize();
				hooks::resize_screen::Initialize();
				init_hook = true;
			}
		}
		return true;
	}
}