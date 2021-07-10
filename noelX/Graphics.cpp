#include "Graphics.h"

Graphics::Graphics()
{
}

Graphics::Graphics(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	scd.BufferCount = 1;
	scd.BufferDesc.Width = 0;
	scd.BufferDesc.Height = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&device,
		nullptr,
		&context
	);
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
	device->CreateRenderTargetView(backBuffer.Get(), nullptr, &rtw);

	D3D11_DEPTH_STENCIL_DESC dsDesc = { 0 };
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>depthStencil;
	device->CreateDepthStencilState(&dsDesc, &depthStencil);
	context->OMSetDepthStencilState(depthStencil.Get(), 1u);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthMask;
	D3D11_TEXTURE2D_DESC depthMaskDesc = { 0 };
	depthMaskDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthMaskDesc.ArraySize = 1u;
	depthMaskDesc.MipLevels = 1u;
	depthMaskDesc.Usage = D3D11_USAGE_DEFAULT;
	depthMaskDesc.SampleDesc.Count = 1u;
	depthMaskDesc.SampleDesc.Quality = 0u;
	depthMaskDesc.Height = 768u;
	depthMaskDesc.Width = 1024u;
	depthMaskDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	device->CreateTexture2D(&depthMaskDesc, nullptr, &depthMask);


	D3D11_DEPTH_STENCIL_VIEW_DESC dswDesc = { };
	dswDesc.Format = DXGI_FORMAT_D32_FLOAT;
	dswDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dswDesc.Texture2D.MipSlice = 0u;
	device->CreateDepthStencilView(depthMask.Get(), &dswDesc, &dsw);

	//render target view
	context->OMSetRenderTargets(1u, rtw.GetAddressOf(), dsw.Get());

	ImGui_ImplDX11_Init(device.Get(), context.Get()); //gui dx11 init
	
}

Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();
}

void Graphics::createResources()
{
	/*auto createShadersTask = Concurrency::create_task([this]() 
	{
		
	});
	auto createGeometryTask = createShadersTask.then([this]()
	{
		
	});*/
}

void Graphics::flipBackBuffer()
{
	swapChain->Present(1u, 0u);
}

void Graphics::clearBuffer(float r, float g, float b)
{
	const float color[] = { r, g, b, 1.0f };
	context->ClearRenderTargetView(rtw.Get(), color);
	context->ClearDepthStencilView(dsw.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

ID3D11Device* Graphics::getDevice()
{
	return device.Get();
}
IDXGISwapChain* Graphics::getSwapChain()
{
	return swapChain.Get();
}
ID3D11DeviceContext* Graphics::getContext()
{
	return context.Get();
}

void Graphics::draw()
{
	context->DrawIndexed(36, 0u, 0u);
}
