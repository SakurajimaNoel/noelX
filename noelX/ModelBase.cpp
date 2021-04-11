#include "ModelBase.h"


void ModelBase::setVSConstantBuffer(Graphics& gfx, float angle)
{
	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};
	const ConstantBuffer cb =
	{
		{
			DirectX::XMMatrixTranspose
			(
				DirectX::XMMatrixRotationZ(angle) *
				DirectX::XMMatrixRotationY(angle) *
				DirectX::XMMatrixTranslation(0.0f, 0.0f, 2.0f) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f)

			)
		}
	};

	D3D11_BUFFER_DESC vsConstBuffDesc = { 0 };
	vsConstBuffDesc.ByteWidth = sizeof(cb);
	vsConstBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	vsConstBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vsConstBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vsConstBuffDesc.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA vsConstSubResData = { 0 };
	vsConstSubResData.pSysMem = &cb;

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVSConstantBuffer;
	gfx.getDevice()->CreateBuffer(&vsConstBuffDesc, &vsConstSubResData, &pVSConstantBuffer);
	gfx.getContext()->VSSetConstantBuffers(0u, 1u, pVSConstantBuffer.GetAddressOf());
}

void ModelBase::setPSConstantBuffer(Graphics& gfx)
{

	struct ConstantBufferPS
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} side_color[6];
	};

	const ConstantBufferPS cbps =
	{
		{
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 1.0f},
			{1.0f, 1.0f, 1.0f},
			{1.0f, 0.0f, 1.0f}
		}
	};

	D3D11_BUFFER_DESC psBuffDesc = { 0 };
	psBuffDesc.ByteWidth = sizeof(cbps);
	psBuffDesc.Usage = D3D11_USAGE_DYNAMIC;
	psBuffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	psBuffDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	psBuffDesc.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA psConstSubResData = { 0 };
	psConstSubResData.pSysMem = &cbps;

	Microsoft::WRL::ComPtr<ID3D11Buffer> pPSConstantBuffer;
	gfx.getDevice()->CreateBuffer(&psBuffDesc, &psConstSubResData, &pPSConstantBuffer);
	gfx.getContext()->PSSetConstantBuffers(0u, 1u, pPSConstantBuffer.GetAddressOf());

}

void ModelBase::setVertexBuffer(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;

	struct Vertex
	{
		DirectX::XMFLOAT3 position;
	}pos;

	Vertex vertices[] =
	{
		{DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f)},
		{DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f)},
		{DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f)},
		{DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f)},
	};


	D3D11_BUFFER_DESC bufferDesc = { 0 };
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0u;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA subResData = { 0 };//idk fam
	subResData.pSysMem = vertices;

	gfx.getDevice()->CreateBuffer(&bufferDesc, &subResData, &pVertexBuffer);

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	gfx.getContext()->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

}

void ModelBase::setIndexBuffer(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;

	const unsigned short int indices[] =
	{
		0,2,1,	2,3,1,
		1,3,5, 	3,7,5,
		2,6,3, 	3,6,7,
		4,5,7, 	4,7,6,
		0,4,2, 	2,4,6,
		0,1,4, 	1,5,4,
	};

	//16 bit index buffer gives around 64k traingles, change to 32bit uint if needed.

	D3D11_BUFFER_DESC indexBufferDesc = { 0 };
	indexBufferDesc.ByteWidth = sizeof(indices);
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;


	D3D11_SUBRESOURCE_DATA indexSubResData = { 0 };
	indexSubResData.pSysMem = indices;

	gfx.getDevice()->CreateBuffer(&indexBufferDesc, &indexSubResData, &pIndexBuffer);

	gfx.getContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

}

void ModelBase::setPixelShader(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;

	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	D3DReadFileToBlob(L"PixelShader.cso", &blob);
	gfx.getDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pPixelShader);

	gfx.getContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}

void ModelBase::setVertexShaderAndIA(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;

	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	D3DReadFileToBlob(L"VertexShader.cso", &blob);
	gfx.getDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pVertexShader);

	gfx.getContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> iLayout;
	const D3D11_INPUT_ELEMENT_DESC iDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};
	gfx.getDevice()->CreateInputLayout(iDesc, (UINT)std::size(iDesc), blob->GetBufferPointer(), blob->GetBufferSize(), &iLayout);
	gfx.getContext()->IASetInputLayout(iLayout.Get());
}

void ModelBase::setRasterizer(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterState;

	D3D11_RASTERIZER_DESC rsDesc;
	rsDesc.FillMode = D3D11_FILL_SOLID;
	rsDesc.CullMode = D3D11_CULL_BACK;
	rsDesc.FrontCounterClockwise = true;
	rsDesc.DepthBias = false;
	rsDesc.DepthBiasClamp = 0;
	rsDesc.SlopeScaledDepthBias = 0;
	rsDesc.DepthClipEnable = true;
	rsDesc.ScissorEnable = true;
	rsDesc.MultisampleEnable = true;
	rsDesc.AntialiasedLineEnable = true;

	gfx.getDevice()->CreateRasterizerState(&rsDesc, &pRasterState);
	gfx.getContext()->RSSetState(pRasterState.Get());
}

void ModelBase::setTopology(Graphics& gfx)
{
	gfx.getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void ModelBase::setViewport(Graphics& gfx)
{
	D3D11_VIEWPORT vwp = { 0 };
	vwp.TopLeftX = 0;
	vwp.TopLeftY = 0;
	vwp.Width = 1024;//640
	vwp.Height = 768;	//480
	vwp.MinDepth = 0;
	vwp.MaxDepth = 1;
	gfx.getContext()->RSSetViewports(1u, &vwp);
}