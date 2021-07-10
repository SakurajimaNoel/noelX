#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include<d3d11.h>
#include<d3dcompiler.h>
#include<array>
#include<wrl.h>
#include<DirectXMath.h>
#include<ppltasks.h>
#include "imgui\imgui_impl_dx11.h"

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics();
	~Graphics();
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void flipBackBuffer();
	void clearBuffer(float r, float g, float b);
	void createResources();
	void draw();
	ID3D11Device* getDevice();
	IDXGISwapChain* getSwapChain();
	ID3D11DeviceContext* getContext();



private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtw;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsw;

};