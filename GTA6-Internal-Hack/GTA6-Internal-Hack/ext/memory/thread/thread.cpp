#include"thread.hpp"

__declspec(dllexport) void InitThread(pSysMem mMemory) {
	if (mMemory != NULL && mMemory->dwEP != NULL) {
		InitMem CallMem = (InitMem)mMemory->dwEP;
		CallMem(mMemory->dwParam);
	}
}

DWORD64 __stdcall Module::GetModuleSize(DWORD64 ModuleImage)
{
	this->dos_header = *(IMAGE_DOS_HEADER*)ModuleImage;
	this->nt_headers = *(IMAGE_NT_HEADERS*)(ModuleImage + this->dos_header.e_lfanew);
	return (DWORD64)this->nt_headers.OptionalHeader.SizeOfImage;
}

PBYTE __stdcall Module::GetModuleBytes(HMODULE Inst, DWORD64 ModuleSize, DWORD64 HexCode)
{
	this->RetBuffer = (PBYTE)Inst + ModuleSize - HexCode;
	return this->RetBuffer;
}

HMODULE Module::GetModuleBase(LPCSTR ModuleName)
{
	this->hModule = spoof_call_ex(JmpRbx, GetModuleHandleA, ModuleName);
	return this->hModule;
}

HANDLE __stdcall Thread::NTRemoteThread(HANDLE Handle, LPSECURITY_ATTRIBUTES Attr, SIZE_T Size, LPTHREAD_START_ROUTINE StartRoutine, LPVOID Buffer, DWORD Flags, LPDWORD ThreadId)
{
	auto ret_addr = spoof_call_ex(JmpRbx, CreateRemoteThread, Handle, Attr, Size, StartRoutine, Buffer, Flags, ThreadId);
	return ret_addr;
}

HANDLE __stdcall Thread::NTMakeThread(LPTHREAD_START_ROUTINE StartRoutine, LPVOID Buffer, LPDWORD ThreadId)
{
	this->hModule = pModule->GetModuleBase("ntdll.dll");
	this->hModuleSize = pModule->GetModuleSize((DWORD64)this->hModule);
	this->hModuleBytes = pModule->GetModuleBytes(this->hModule, this->hModuleSize, 0x400);

	pWinApi->NTVirtualProtect(this->hModuleBytes, 0x100, PAGE_EXECUTE_READWRITE, &this->hProtect);
	pSysMem mMemory = (pSysMem)pWinApi->NTVirtualAlloc(NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	mMemory->dwEP = (DWORD64)(StartRoutine);
	mMemory->dwParam = Buffer;

	memcpy((LPVOID)this->hModuleBytes, (LPVOID)InitThread, 0x100);
	this->hRemoteThread = this->NTRemoteThread(pWinApi->CurrentProcess(), 0, 0x100, (LPTHREAD_START_ROUTINE)this->hModuleBytes, mMemory, 0, ThreadId);
	pWinApi->ExitHandle(this->hRemoteThread);
	return NULL;
}
