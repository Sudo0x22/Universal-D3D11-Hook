#include"../ext/ext.hpp"

__declspec(dllexport) void __stdcall MainThread(HMODULE hModule, LPVOID hBuffer)
{
	while (!pModule->GetModuleBase(NULL))
		Sleep(420);

	pOffsets.Initialize();
	pFeatures->Initialize();
}

__declspec(dllexport) bool __stdcall DllMain(HMODULE hModule, DWORD hReasons, LPVOID hBuffer)
{
	if (hReasons != DLL_PROCESS_ATTACH)
		return false;

	Globals globals = {};
	globals.RemoteThread = pThread->NTMakeThread((LPTHREAD_START_ROUTINE)MainThread, 0, 0);
	pWinApi->ExitHandle(globals.RemoteThread);
	
	globals.OverlayThread = pThread->NTMakeThread((LPTHREAD_START_ROUTINE)Hooks::Initialize, 0, 0);
	pWinApi->ExitHandle(globals.OverlayThread);

	return true;
}