#include "Cube.h"

Cube::Cube(Graphics& gfx)
{
	initVSConstantBuffer(gfx, cbvs,0u);
	//initPSConstantBuffer(gfx, cbps);
	initIndexBuffer(gfx, indices);
	initPixelShader(gfx, pixelShader);
	initRasterizer(gfx, D3D11_CULL_BACK);
	initSampler(gfx);
	initTexture(gfx, texture);
	setTopology(gfx, topology);
	initVertexBuffer(gfx, vertices);
	initVertexShaderAndIA(gfx, vertexShader, idesc);
	initViewport(gfx);
}

void Cube::updateTransform(Graphics& gfx, DirectX::XMFLOAT3 pos)
{
	cbvs =
	{
		{
			DirectX::XMMatrixTranspose
			(
				//DirectX::XMMatrixRotationZ(angle) *
				//DirectX::XMMatrixRotationY(angle) *
				gfx.getCamera()*
				DirectX::XMMatrixTranslation(-pos.x, pos.y, -pos.z) *
				DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f) //projection matrix
				//DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), 1024/768, 0.4f, 100.0f)
				
				

			)
		}
	};

	initVSConstantBuffer(gfx, cbvs,0u);
}

void Cube::bindAndDrawI(Graphics& gfx)
{
	bindResources(gfx);
	gfx.drawIndexed(indices.size());
}
