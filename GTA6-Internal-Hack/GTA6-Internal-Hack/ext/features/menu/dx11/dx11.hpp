#pragma once
#include"../defines/defines.hpp"

class NtCreateWindow
{
public:
	ATOM WINAPI NtRegisterWnd(const WNDCLASSEX* oWndClass) {
		return spoof_call_ex(JmpRbx, RegisterClassEx, oWndClass);
	}
	ATOM WINAPI NtUnregisterWnd(LPCWSTR Class, _In_ HINSTANCE hInst) {
		return spoof_call_ex(JmpRbx, UnregisterClass, Class, hInst);
	}
	BOOL WINAPI NtDeleteWindow(HWND hWindow) {
		return spoof_call_ex(JmpRbx, DestroyWindow, hWindow);
	}
	HWND WINAPI NtCreateWindowEx(DWORD Exit, LPCWSTR Class, LPCWSTR Name, DWORD Style, int x, int y, int w, int h, HWND hWindow,
		HMENU hMenu, HINSTANCE hInst, LPVOID Param) {
		return spoof_call_ex(JmpRbx, CreateWindowExW, Exit, Class, Name, Style, x, y, w, h, hWindow, hMenu, hInst, Param);
	}

}; NtCreateWindow* pWindowEx = new NtCreateWindow();

class DX11 {
public:
	__declspec(dllexport) bool init_window()
	{
		pD3D11->WindowClass.cbSize = sizeof(WNDCLASSEX);
		pD3D11->WindowClass.style = CS_HREDRAW | CS_VREDRAW;
		pD3D11->WindowClass.lpfnWndProc = DefWindowProc;

		pD3D11->WindowClass.cbClsExtra = 0;
		pD3D11->WindowClass.cbWndExtra = 0;
		pD3D11->WindowClass.hInstance = pModule->GetModuleBase(NULL);

		pD3D11->WindowClass.hIcon = NULL;
		pD3D11->WindowClass.hCursor = NULL;
		pD3D11->WindowClass.hbrBackground = NULL;

		pD3D11->WindowClass.lpszMenuName = NULL;
		pD3D11->WindowClass.lpszClassName = L"OK";
		pD3D11->WindowClass.hIconSm = NULL;

		pWindowEx->NtRegisterWnd(&pD3D11->WindowClass);
		pD3D11->WindowHandle = pWindowEx->NtCreateWindowEx(NULL, pD3D11->WindowClass.lpszClassName, L"GTA Window",
			WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, pD3D11->WindowClass.hInstance, NULL);
		if (pD3D11->WindowHandle == NULL) { return false; }

		return true;
	}
	__declspec(dllexport) bool delete_window()
	{
		pWindowEx->NtDeleteWindow(pD3D11->WindowHandle);
		pWindowEx->NtUnregisterWnd(pD3D11->WindowClass.lpszClassName, pD3D11->WindowClass.hInstance);
		if (pD3D11->WindowHandle != NULL) { return false; }
		return true;
	}
	__declspec(dllexport) bool initialize()
	{
		if (this->init_window() == false) { this->delete_window(); return false; }

		HINSTANCE hModule = pModule->GetModuleBase("d3d11.dll");
		void* D3D11CreateDeviceSwapChain = pModule->GetProcAddr(hModule, "D3D11CreateDeviceAndSwapChain");

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

		DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = pD3D11->WindowHandle;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* context;

		if (((long(__stdcall*)(
			IDXGIAdapter*,
			D3D_DRIVER_TYPE,
			HMODULE,
			UINT,
			const D3D_FEATURE_LEVEL*,
			UINT,
			UINT,
			const DXGI_SWAP_CHAIN_DESC*,
			IDXGISwapChain**,
			ID3D11Device**,
			D3D_FEATURE_LEVEL*,
			ID3D11DeviceContext**))(D3D11CreateDeviceSwapChain))(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &context) < 0)
		{
			this->delete_window();
			return false;
		}

		MethodsTableX64 = (uint64_t*)calloc(205, sizeof(uint64_t));
		pWinApi->NTMemCpy(MethodsTableX64, *(uint64_t**)swapChain, 18 * sizeof(uint64_t));
		pWinApi->NTMemCpy(MethodsTableX64 + 18, *(uint64_t**)device, 43 * sizeof(uint64_t));
		pWinApi->NTMemCpy(MethodsTableX64 + 18 + 43, *(uint64_t**)context, 144 * sizeof(uint64_t));

		MH_Initialize();

		swapChain->Release();
		swapChain = NULL;

		device->Release();
		device = NULL;

		context->Release();
		context = NULL;

		this->delete_window();
		return true;
	}
}; DX11* pDX11 = new DX11();