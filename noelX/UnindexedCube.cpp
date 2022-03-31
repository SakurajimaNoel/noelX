#include "UnindexedCube.h"

UnindexedCube::UnindexedCube(Graphics& gfx)
{
	initVSConstantBuffer(gfx, vertexCBuff, 0u);
	colorCBuff.color = material;
	initPSConstantBuffer(gfx, colorCBuff, 1);
	//initIndexBuffer(gfx, indices);
	initPixelShader(gfx, pixelShader);
	initRasterizer(gfx, D3D11_CULL_BACK);
	//initSampler(gfx);
	//initTexture(gfx, texture);
	setTopology(gfx, topology);
	initVertexBuffer(gfx, vertices);
	initVertexShaderAndIA(gfx, vertexShader, idesc);
	initViewport(gfx);
}

void UnindexedCube::updateTransform(Graphics& gfx)
{
	
	vertexCBuff.modelView = DirectX::XMMatrixIdentity() * gfx.getCamera();
	vertexCBuff.modelViewProjection = DirectX::XMMatrixTranspose
	(
		vertexCBuff.modelView * //model
		//gfx.getCamera() * //view
		DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f) //projection matrix
	);
	
	
	
	/*cbvs =
	{
		{
			DirectX::XMMatrixTranspose
			(
				gfx.getCamera() *  
				DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.4f, 100.0f) //projection matrix
				
			)
		}
	};*/

	initVSConstantBuffer(gfx, vertexCBuff, 0u);
}

void UnindexedCube::bindAndDraw(Graphics& gfx)
{
	bindResources(gfx);
	gfx.draw(vertices.size());
}
