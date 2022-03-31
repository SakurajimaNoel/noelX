#include "Skybox.h"

Skybox::Skybox(Graphics& gfx)
{
	initVSConstantBuffer(gfx, vertexCBuff,0u);
	initIndexBuffer(gfx, indices);
	initPixelShader(gfx, pixelShader);
	initRasterizer(gfx, D3D11_CULL_NONE);
	initSampler(gfx);
	initTexture(gfx, texture);
	setTopology(gfx, topology);
	initVertexBuffer(gfx, vertices);
	initVertexShaderAndIA(gfx, vertexShader, idesc);
	initViewport(gfx);

	DirectX::XMStoreFloat3x3(&skyboxTransform, DirectX::XMMatrixIdentity());
}

void Skybox::updateTransform(Graphics& gfx)
{
	DirectX::XMStoreFloat3x3(&skyboxTransform, gfx.getCamera());
	vertexCBuff.transform =


		DirectX::XMMatrixTranspose
		(
			DirectX::XMLoadFloat3x3(&skyboxTransform) *
			//DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)*
			DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f) //projection matrix
			//DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), 1024/768, 0.4f, 100.0f)
		);
		
	

	initVSConstantBuffer(gfx, vertexCBuff,0u);
}

void Skybox::bindAndDrawI(Graphics& gfx)
{
	bindResources(gfx);
	gfx.drawIndexed(indices.size());
}
