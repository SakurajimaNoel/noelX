#pragma once
#include "Graphics.h"
#include <WICTextureLoader.h>
#include <DirectXHelpers.h>
#include <DDSTextureLoader.h>
class ModelBase 
{
protected:
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVSConstantBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pPSConstantBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> iLayout = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srw = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> smplr = nullptr;
	
	UINT stride = 0;
	const UINT offset = 0u;

	template <class VS>
	void initVSConstantBuffer(Graphics& gfx, const std::vector<VS>& cbvs) 
	{
		D3D11_BUFFER_DESC vsConstBuffDesc = { 0 };
		vsConstBuffDesc.ByteWidth = UINT(sizeof(VS) * cbvs.size());
		vsConstBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
		vsConstBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		vsConstBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		vsConstBuffDesc.MiscFlags = 0u;
		vsConstBuffDesc.StructureByteStride = sizeof(VS);

		D3D11_SUBRESOURCE_DATA vsConstSubResData = { 0 };
		vsConstSubResData.pSysMem = cbvs.data();

		
		gfx.getDevice()->CreateBuffer(&vsConstBuffDesc, &vsConstSubResData, &pVSConstantBuffer);
		gfx.getContext()->VSSetConstantBuffers(0u, 1u, pVSConstantBuffer.GetAddressOf());

	}

	template <class PS>
	void initPSConstantBuffer(Graphics& gfx, const std::vector<PS>& cbps)
	{
		D3D11_BUFFER_DESC psBuffDesc = { 0 };
		psBuffDesc.ByteWidth = UINT(sizeof(PS) * cbps.size());
		psBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
		psBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		psBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		psBuffDesc.MiscFlags = 0u;
		psBuffDesc.StructureByteStride = sizeof(PS);
		D3D11_SUBRESOURCE_DATA psConstSubResData = { 0 };
		psConstSubResData.pSysMem = cbps.data();

		
		gfx.getDevice()->CreateBuffer(&psBuffDesc, &psConstSubResData, &pPSConstantBuffer);
		gfx.getContext()->PSSetConstantBuffers(0u, 1u, pPSConstantBuffer.GetAddressOf());

	}


	template <class T> //weird template shit gives linker error if definition is moved to .cpp
	void initVertexBuffer(Graphics& gfx, const std::vector<T>& vertices) 
	{
		
		D3D11_BUFFER_DESC bufferDesc = { 0 };
		bufferDesc.ByteWidth = UINT(sizeof(T) * vertices.size());
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0u;
		bufferDesc.MiscFlags = 0u;
		bufferDesc.StructureByteStride = sizeof(T);

		D3D11_SUBRESOURCE_DATA subResData = { 0 };//idk fam
		subResData.pSysMem = vertices.data();

		gfx.getDevice()->CreateBuffer(&bufferDesc, &subResData, &pVertexBuffer);

		stride = sizeof(T);

		gfx.getContext()->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	}

	void initTexture(Graphics& gfx, LPCWSTR& texture);
	void initSampler(Graphics& gfx);
	void initIndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices);
	void initPixelShader(Graphics& gfx, LPCWSTR psShader);
	void initVertexShaderAndIA(Graphics& gfx, LPCWSTR vsShader, const std::vector<D3D11_INPUT_ELEMENT_DESC>& idesc);
	void initRasterizer(Graphics& gfx, enum D3D11_CULL_MODE cullMode);
	void setTopology(Graphics& gfx, D3D_PRIMITIVE_TOPOLOGY topology);
	void initViewport(Graphics& gfx);

	void bindResources(Graphics& gfx);
	/*void bindVSConstBuffer();
	void bindPSConstBuffer();
	void bindIndexBuffer();
	void bindVertexBuffer();
	void bindPixelShader();
	void bindVertexShaderIA();*/
};