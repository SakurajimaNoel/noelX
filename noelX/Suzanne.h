#pragma once
#include "ModelBase.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
class Suzanne : public ModelBase
{
public:
	Suzanne(Graphics& gfx);
	~Suzanne() = default;
	Suzanne(const Suzanne&) = delete;
	Suzanne& operator=(const Suzanne&) = delete;
	void updateTransform(Graphics& gfx);
	void bindAndDraw(Graphics& gfx);
	float scale = 1.0f;
private:
	LPCWSTR pixelShader = L"PhongPixelShader.cso";
	LPCWSTR vertexShader = L"PhongVertexShader.cso";
	D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	DirectX::XMFLOAT3 material = { 0.0f, 1.0f, 0.5f };
	struct Vertex
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normals;
	};

	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
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
};