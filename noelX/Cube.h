#pragma once
#include "ModelBase.h"
class Cube : public ModelBase
{
public:
	Cube(Graphics& gfx);
	~Cube() = default;
	Cube(const Cube&) = delete;
	Cube& operator=(const Cube&) = delete;
	void updateTransform(Graphics& gfx, DirectX::XMFLOAT3 pos);
	void bindAndDrawI(Graphics& gfx);
private:
	LPCWSTR pixelShader = L"TexturePixelShader.cso";
	LPCWSTR vertexShader = L"VertexShader.cso";
	LPCWSTR texture = L"mlgmap.dds";
	D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	


	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};

	const std::vector<Vertex> vertices =
	{
		{DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT2(1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT2(0.0f, 0.0f)},
	};

	const std::vector<unsigned short> indices =
	{
		0,2,1,	2,3,1,
		1,3,5, 	3,7,5,
		2,6,3, 	3,6,7,
		4,5,7, 	4,7,6,
		0,4,2, 	2,4,6,
		0,1,4, 	1,5,4,
	};

	const std::vector<D3D11_INPUT_ELEMENT_DESC> idesc =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	/*
	struct ConstantBufferPS
	{
			float r;
			float g;
			float b;
			float a;
	};

	const std::vector<ConstantBufferPS> cbps =
	{
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f},
			{1.0f, 0.0f, 1.0f}
	};
	*/
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