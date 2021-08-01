#pragma once
#include "ModelBase.h"

class Pyramid : public ModelBase
{
public:
	Pyramid(Graphics& gfx);
	~Pyramid() = default;
	Pyramid(const Pyramid&) = delete;
	Pyramid& operator=(const Pyramid&) = delete;
	void updateTransform(Graphics & gfx);
	void bindAndDrawI(Graphics & gfx);
private:
	LPCWSTR pixelShader = L"UnindexedTexturePixelShader.cso";
	LPCWSTR vertexShader = L"VertexShader.cso";
	LPCWSTR texture = L"stone.jpg";
	D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;



	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};

	const std::vector<Vertex> vertices =
	{
		{DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.0f, 1.0f, 0.5f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)}
	};


	const std::vector<D3D11_INPUT_ELEMENT_DESC> idesc =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	
	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};

	std::vector<ConstantBuffer> cbvs =
	{
		{
			DirectX::XMMatrixTranspose
			(
				//DirectX::XMMatrixRotationZ(0) *
				//DirectX::XMMatrixRotationY(0) *
				//DirectX::XMMatrixTranslation(0.0f, 0.0f, 2.0f) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f)

			)
		}
	};

};