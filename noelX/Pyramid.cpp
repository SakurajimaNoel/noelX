#include "Pyramid.h"

Pyramid::Pyramid(Graphics& gfx)
{
	initVSConstantBuffer(gfx, cbvs,0u);
	//initPSConstantBuffer(gfx, cbps);
	//initIndexBuffer(gfx, indices);
	initPixelShader(gfx, pixelShader);
	initRasterizer(gfx, D3D11_CULL_BACK);
	initSampler(gfx);
	initTexture(gfx, texture);
	setTopology(gfx, topology);
	initVertexBuffer(gfx, vertices);
	initVertexShaderAndIA(gfx, vertexShader, idesc);
	initViewport(gfx);
}

void Pyramid::updateTransform(Graphics& gfx)
{
	cbvs =
	{
		{
			DirectX::XMMatrixTranspose
			(
				//DirectX::XMMatrixRotationZ(angle) *
				//DirectX::XMMatrixRotationY(angle) *
				gfx.getCamera() *
				//DirectX::XMMatrixTranslation(0.0f, 0.0f, 2.0f) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f) //projection matrix
				//DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), 1024/768, 0.4f, 100.0f)



			)
		}
	};

	initVSConstantBuffer(gfx, cbvs,0u);
}

void Pyramid::bindAndDrawI(Graphics& gfx)
{
	bindResources(gfx);
	gfx.draw(vertices.size());
}
