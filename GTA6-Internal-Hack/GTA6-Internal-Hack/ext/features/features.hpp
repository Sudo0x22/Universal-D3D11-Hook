#pragma once
#include"menu/menu.hpp"
#include"visuals/visuals.hpp"

class Features {
public:
	__declspec(dllexport) void Initialize() 
	{
		static bool unload = false;
		while (!unload) 
		{
			BaseEntity* LocalEnt = GetLocalPlayer();
			if (LocalEnt == NULL)
				continue;


		}
	}
}; Features* pFeatures = new Features();