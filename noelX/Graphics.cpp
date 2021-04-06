#include "Graphics.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")


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


}



void Graphics::flipBackBuffer()
{
	swapChain->Present(1u, 0u);
}

void Graphics::clearBuffer()
{
	const float color[] = { 1.0f, 0.5f, 0.25f, 1.0f };
	context->ClearRenderTargetView(rtw.Get(), color);
}

void Graphics::drawTriangle()
{
	//vertex data

	struct Vertex
	{
		float x;
		float y;
	};

	Vertex vertices[] =
	{
		{0.0f, 0.5f},
		{0.5f, -0.5f},
		{-0.5f, -0.5f}
	};

	//vertex buffer
	Microsoft::WRL::ComPtr<ID3D11Buffer>vertexBuffer;

	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0u;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA subResData = { 0 };//idk fam
	subResData.pSysMem = vertices;

	device->CreateBuffer(&bufferDesc, &subResData, &vertexBuffer);
	
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	context->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);
	
	//pixel shader
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	D3DReadFileToBlob(L"PixelShader.cso", &blob);
	device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
	
	context->PSSetShader(pixelShader.Get(), nullptr, 0u);

	//topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);



	//vertex shader
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	
	D3DReadFileToBlob(L"VertexShader.cso", &blob);
	device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
	
	context->VSSetShader(vertexShader.Get(), nullptr, 0u);

	//render target view
	context->OMSetRenderTargets(1u, rtw.GetAddressOf(), nullptr);

	//viewport config
	D3D11_VIEWPORT vwp = { 0 };
	vwp.TopLeftX = 0;
	vwp.TopLeftY = 0;
	vwp.Width = 640;
	vwp.Height = 480;	
	vwp.MinDepth = 0;
	vwp.MaxDepth = 1;
	context->RSSetViewports(1u, &vwp);

	//Input Layout
	Microsoft::WRL::ComPtr<ID3D11InputLayout> iLayout;
	const D3D11_INPUT_ELEMENT_DESC iDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};
	device->CreateInputLayout(iDesc, (UINT)std::size(iDesc), blob->GetBufferPointer(), blob->GetBufferSize(), &iLayout);
	context->IASetInputLayout(iLayout.Get());

	//draw
	context->Draw(std::size(vertices), 0u);
}
