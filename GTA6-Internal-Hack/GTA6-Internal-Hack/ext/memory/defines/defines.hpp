#pragma once
#include<Windows.h>
#include<cstdint>

typedef unsigned int uint;
typedef struct SysMem {
	DWORD64 dwEP;
	LPVOID dwParam;
}SysMem, * pSysMem;
typedef DWORD(*InitMem)(LPVOID Param);
typedef struct Globals {
	HANDLE ProcID;
	DWORD64 ModuleBase;
	HANDLE RemoteThread;
	HANDLE OverlayThread;
} Globals, * pGlobals;