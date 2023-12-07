#pragma once
#include<d3d11.h>
#include<dxgi.h>
#include"../../../memory/mem.hpp"
#include"../../../hook/hook.hpp"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

typedef HRESULT(__stdcall* oPresentFn)(IDXGISwapChain*, UINT, UINT);
typedef LRESULT(__stdcall* oWndProcFn)(HWND, UINT, WPARAM, LPARAM);
typedef BOOL(__stdcall* oCursorFn)(bool);
typedef HRESULT(__stdcall* oResizeOriginalFn)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

class D3D11 {
public:
	oPresentFn oPresent = 0;
	oWndProcFn oWndProc = 0;
	oCursorFn oCursor = 0;
	oResizeOriginalFn oResizeOriginal = 0;
public:
	ID3D11Device* pDevice;
	ID3D11DeviceContext* pDeviceContext = 0;
	ID3D11RenderTargetView* pRenderTargetView = 0;
public:
	WNDCLASSEX WindowClass = {};
	HWND WindowHandle = 0;
	HWND hWindow = 0;
}; D3D11* pD3D11 = new D3D11();