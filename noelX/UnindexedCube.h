#pragma once
#include "ModelBase.h"
class UnindexedCube : public ModelBase
{
public:
	UnindexedCube(Graphics &gfx);
	~UnindexedCube() = default;
	UnindexedCube(const UnindexedCube&) = delete;
	void updateTransform(Graphics& gfx);
	void bindAndDraw(Graphics& gfx);
	DirectX::XMFLOAT3 material = { 0.0f, 1.0f, 0.5f };
	DirectX::XMMATRIX model = DirectX::XMMatrixIdentity();
private:
	LPCWSTR pixelShader = L"PhongPixelShader.cso";
	LPCWSTR vertexShader = L"PhongVertexShader.cso";
	D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normals;
	};

	const std::vector<Vertex> vertices =
	{
		//leftface
		{DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f)},

		//frontface
		{DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f),DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f)},

		//Topface
		{DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f)},

		//rightface
		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f)},

		//backface
		{DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f),DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f),DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f),DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f)},


		//topface
		{DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)},
		{DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)},


	};

	const std::vector<D3D11_INPUT_ELEMENT_DESC> idesc =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	struct ConstantBuffer
	{
		DirectX::XMMATRIX modelView = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX modelViewProjection = DirectX::XMMatrixTranspose
		(
			DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f)
		);

	} vertexCBuff;

	struct PSMaterialConstantBuffer
	{
		alignas(16) DirectX::XMFLOAT3 color;
		float specularIntensity = 0.6f;
		float specularPower = 30.0f;
		float padding[2];
	} colorCBuff;
	


	/*std::vector<ConstantBuffer>cbvs =
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
	*/
};