#include "ModelBase.h"


void ModelBase::setIndexBuffer(Graphics& gfx, const std::vector<unsigned short>& indices)
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;

	
	D3D11_BUFFER_DESC indexBufferDesc = { 0 };
	indexBufferDesc.ByteWidth = UINT(sizeof(unsigned short) * indices.size());
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0u;
	indexBufferDesc.MiscFlags = 0u;
	indexBufferDesc.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indexSubResData = { 0 };
	indexSubResData.pSysMem = indices.data();

	gfx.getDevice()->CreateBuffer(&indexBufferDesc, &indexSubResData, &pIndexBuffer);

	gfx.getContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

}

void ModelBase::setPixelShader(Graphics& gfx, LPCWSTR psShader)
{
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;

	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	D3DReadFileToBlob(psShader, &blob);
	gfx.getDevice()->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pPixelShader);

	gfx.getContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}

void ModelBase::setVertexShaderAndIA(Graphics& gfx, LPCWSTR vsShader, const std::vector<D3D11_INPUT_ELEMENT_DESC>& idesc)
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;

	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	D3DReadFileToBlob(vsShader, &blob);
	gfx.getDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pVertexShader);

	gfx.getContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> iLayout;
	
	gfx.getDevice()->CreateInputLayout(idesc.data(), (UINT)idesc.size(), blob->GetBufferPointer(), blob->GetBufferSize(), &iLayout);
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

void ModelBase::setTopology(Graphics& gfx, D3D_PRIMITIVE_TOPOLOGY topology)
{
	gfx.getContext()->IASetPrimitiveTopology(topology);
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

void ModelBase::setTexture(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	
	//Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	//resource.As(&tex);

	//CD3D11_TEXTURE2D_DESC texDesc;
	//tex->GetDesc(&texDesc);

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srw;
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(gfx.getDevice(), L"mlgmap.dds", 0, D3D11_USAGE_IMMUTABLE, D3D11_BIND_SHADER_RESOURCE, 0, D3D11_RESOURCE_MISC_TEXTURECUBE, false, resource.GetAddressOf(), srw.GetAddressOf());
	if (FAILED(hr))
	{
		OutputDebugString(L"Texture loading failed");
	}
	
	gfx.getContext()->PSSetShaderResources(0u, 1u, srw.GetAddressOf());
}

void ModelBase::setSampler(Graphics& gfx)
{
	Microsoft::WRL::ComPtr<ID3D11SamplerState> smplr;

	D3D11_SAMPLER_DESC smpDesc = {};
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	gfx.getDevice()->CreateSamplerState(&smpDesc, &smplr);
	gfx.getContext()->PSSetSamplers(0u, 1u, smplr.GetAddressOf());
	

}