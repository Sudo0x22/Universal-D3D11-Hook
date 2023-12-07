#pragma once
#include<Windows.h>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include"../spoofer/spoofer.hpp"

#pragma section(".text")
__declspec(allocate(".text")) unsigned const char JmpRbx[] = { 0xff, 0x23 };
#define AddPointer(cClass, szName) namespace F { inline cClass szName; }

class WinApi
{
public:
	__declspec(dllexport) HANDLE WINAPI CurrentProcess() {
		auto ret_addr = spoof_call_ex(JmpRbx, GetCurrentProcess);
		return ret_addr; }
	__declspec(dllexport) BOOL WINAPI NTVirtualProtect(LPVOID Inst, SIZE_T Size, DWORD OldProtect, PDWORD NewProtect) {
		auto ret_addr = spoof_call_ex(JmpRbx, VirtualProtect, Inst, Size, OldProtect, NewProtect);
		return ret_addr; }
	__declspec(dllexport) LPVOID WINAPI NTVirtualAlloc(LPVOID Inst, SIZE_T Size, DWORD AllocType, DWORD Protect) {
		auto ret_addr = spoof_call_ex(JmpRbx, VirtualAlloc, Inst, Size, AllocType, Protect);
		return ret_addr; }
	__declspec(dllexport) BOOL WINAPI ExitHandle(HANDLE Handle) {
		auto ret_addr = spoof_call_ex(JmpRbx, CloseHandle, Handle);
		return ret_addr; }
	__declspec(dllexport) LPVOID WINAPI NTMemCpy(void* inst, const void* ptr, size_t size) {
		auto ret_addr = spoof_call_ex(JmpRbx, memcpy, inst, ptr, size);
		return ret_addr;}
	__declspec(dllexport) LONG_PTR WINAPI NtSetWindowLongPtr(_In_ HWND hWindow, _In_ INT hIndex, _In_ LONG_PTR dwLong) {
			return spoof_call_ex(JmpRbx, SetWindowLongPtrW, hWindow, hIndex, dwLong);}
	__declspec(dllexport) LRESULT WINAPI CallWndProc(_In_ WNDPROC WndProc, _In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) {
		return spoof_call_ex(JmpRbx, CallWindowProcW, WndProc, hWnd, uMsg, wParam, lParam);}
}; WinApi* pWinApi = new WinApi();