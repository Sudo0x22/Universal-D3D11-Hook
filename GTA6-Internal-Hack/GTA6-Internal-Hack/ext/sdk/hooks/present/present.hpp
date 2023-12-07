#pragma once
#include"../wndproc/wndproc.hpp"

namespace hooks
{
	//inline Hook* pHook = nullptr;
	namespace present
	{
		using Fn = HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT);
		HRESULT __fastcall Detour(IDXGISwapChain* pSwapChain, UINT uInt, UINT uFlags) {
			
			if (!pOverlay->init_imgui)
			{
				if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (LPVOID*)&pD3D11->pDevice)))
				{
					ImGui::CreateContext();

					pD3D11->pDevice->GetImmediateContext(&pD3D11->pDeviceContext);
					DXGI_SWAP_CHAIN_DESC desc;

					pSwapChain->GetDesc(&desc);
					pD3D11->hWindow = desc.OutputWindow;

					ID3D11Texture2D* pBackBuffer;
					pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

					D3D11_RENDER_TARGET_VIEW_DESC RenderTarget = {};
					memset(&RenderTarget, 0, sizeof(RenderTarget));

					RenderTarget.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
					RenderTarget.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

					pD3D11->pDevice->CreateRenderTargetView(pBackBuffer, &RenderTarget, &pD3D11->pRenderTargetView);
					pBackBuffer->Release();

					ImGui::GetIO().ImeWindowHandle = pD3D11->hWindow;
					ImGui_ImplDX11_CreateDeviceObjects();

					pD3D11->oWndProc = (oWndProcFn)pWinApi->NtSetWindowLongPtr(pD3D11->hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc::Detour);
					pImGui->Initialize();
					pOverlay->init_imgui = true;
				}
				else
					return pD3D11->oPresent(pSwapChain, uInt, uFlags);
			}

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::GetIO().MouseDrawCursor = pOverlay->render_overlay;
			ImGui::GetIO().WantCaptureMouse = pOverlay->render_overlay;

			if (GetAsyncKeyState(VK_INSERT) & 0x1) { pOverlay->render_overlay = !pOverlay->render_overlay; }
			if (pOverlay->render_overlay) { pOverlay->RenderImGui("Menu"); }

			ImGui::EndFrame();
			ImGui::Render();
			pD3D11->pDeviceContext->OMSetRenderTargets(1, &pD3D11->pRenderTargetView, NULL);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			return pD3D11->oPresent(pSwapChain, uInt, uFlags);
		}
		__declspec(dllexport) void Initialize() {
			pHook->MakeHook(8, Detour, (void**)&pD3D11->oPresent);
		}
	}

	namespace resize_screen
	{
		using Fn = HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT );
		HRESULT __fastcall Detour(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
		{
			ImGui_ImplDX11_Shutdown();
			pD3D11->pRenderTargetView->Release();
			pD3D11->pDeviceContext->Release();
			pD3D11->pDevice->Release();
			pD3D11->pDevice = nullptr;
			return pD3D11->oResizeOriginal(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
		}
		__declspec(dllexport) void Initialize() {
			pHook->MakeHook(13, Detour, (void**)&pD3D11->oResizeOriginal);
		}
	}
}