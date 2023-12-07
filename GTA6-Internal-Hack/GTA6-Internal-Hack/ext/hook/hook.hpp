#pragma once
#include<cstdint>
#include<cassert>
#include"minhook/include/MinHook.h"

static uint64_t* MethodsTableX64 = nullptr;
static uint32_t* MethodsTableX86 = nullptr;

class SpoofHook {
public:
	__declspec(dllexport) MH_STATUS CreateHook(LPVOID Target, LPVOID Detour, LPVOID* Original) {
		auto ret_addr = spoof_call_ex(JmpRbx, MH_CreateHook, Target, Detour, Original);
		return ret_addr;
	}
	__declspec(dllexport) MH_STATUS EnableHook(LPVOID Target) {
		auto ret_addr = spoof_call_ex(JmpRbx, MH_EnableHook, Target);
		return ret_addr;
	}
public:
	__declspec(dllexport) MH_STATUS DisableHook(LPVOID Target) {
		auto ret_addr = spoof_call_ex(JmpRbx, MH_DisableHook, Target);
		return ret_addr;
	}
	__declspec(dllexport) MH_STATUS RemoveHook(LPVOID Target) {
		auto ret_addr = spoof_call_ex(JmpRbx, MH_RemoveHook, Target);
		return ret_addr;
	}
};

class Hook : public SpoofHook {
public:
	__declspec(dllexport) bool MakeHook(uint16_t nIndex, void* nDetour, void** nOriginal) {
		assert(index >= 0 && detour != NULL && original != NULL);
		void* nTarget = (void*)MethodsTableX64[nIndex];
		if (this->CreateHook(nTarget, nDetour, nOriginal) != MH_STATUS::MH_OK)
			return false;
		if (this->EnableHook(nTarget) != MH_STATUS::MH_OK)
			return false;
		return true;
	}
	__declspec(dllexport) void KillHook(uint16_t nIndex) {
		this->DisableHook((void*)MethodsTableX64[nIndex]);
		this->RemoveHook((void*)MethodsTableX64[nIndex]);
	}
}; Hook* pHook = new Hook();