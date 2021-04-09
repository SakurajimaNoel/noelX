#pragma once
#include<d3d11.h>
#include<d3dcompiler.h>
#include<array>
#include<wrl.h>
#include<DirectXMath.h>
class Graphics
{
public:
	Graphics(HWND hWnd);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void flipBackBuffer();
	void clearBuffer(float r, float g, float b);
	void drawTriangle(float angle);
private:
	
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtw;
};