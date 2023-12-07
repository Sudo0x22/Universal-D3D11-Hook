#pragma once
#include"../../../memory/mem.hpp"
/*
	Universal X64 Dll For Most Titles
	Just Replace The Class After pOffsets
	EG: pOffsets.pApex.GlowEnabled = 0x12C3

	Initialize Offsets In The Right ModuleBase If statement in Initialize();
*/
class Offsets {
public:
	uintptr_t module_base = 0x00;
public:
	class DeadByDaylight
	{
	public:
		uintptr_t m_vVewRender = 0x00;
	}; DeadByDaylight pDeadByDaylight;
	class Warzone {
	public:
		uintptr_t m_vVewRender = 0x00;
	}; Warzone pWarzone;
	class Apex {
	public:
		uintptr_t m_vVewRender = 0x00;
	}; Apex pApex;
public:
	__declspec(dllexport) bool Initialize() 
	{
		this->module_base = (uintptr_t)pModule->GetModuleBase(NULL);
		
		if (pModule->GetModuleBase("DeadByDaylight.exe")) 
		{
			this->pDeadByDaylight.m_vVewRender = 0x1C4D4;
		}
		if (pModule->GetModuleBase("Cod.exe")) 
		{
			this->pWarzone.m_vVewRender = 0x20C43D;
		}
		if (pModule->GetModuleBase("r5apex.exe")) 
		{
			this->pApex.m_vVewRender = 0x1C33D;
		}

		return true;
	}
}; Offsets pOffsets;