#pragma once
#include "ModelBase.h"
class Skybox : public ModelBase
{
public:
	Skybox(Graphics& gfx);
	~Skybox() = default;
	Skybox(const Skybox&) = delete;
	Skybox& operator=(const Skybox&) = delete;
	void updateTransform(Graphics& gfx);
	void bindAndDrawI(Graphics& gfx);
private:
	LPCWSTR pixelShader = L"TexturePixelShader.cso";
	LPCWSTR vertexShader = L"SkyboxVertexShader.cso";
	LPCWSTR texture = L"skybox.dds";
	D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	DirectX::XMFLOAT3X3 skyboxTransform;
	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};

	const std::vector<Vertex> vertices =
	{
		{DirectX::XMFLOAT3(-1.0f,-1.0f,-1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-1.0f,-1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f,-1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)},
		{DirectX::XMFLOAT3(1.0f,-1.0f,-1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(1.0f,-1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f,-1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
		{DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)},
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


	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};

	std::vector<ConstantBuffer> cbvs =
	{
		{
			DirectX::XMMatrixTranspose
			(
				//DirectX::XMMatrixTranslation(0.0f, 0.0f, 2.0f) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f)

			)
		}
	};
};