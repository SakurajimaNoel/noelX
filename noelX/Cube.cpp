#include "Cube.h"

Cube::Cube(Graphics& gfx)
{
	setVSConstantBuffer(gfx, cbvs);
	setPSConstantBuffer(gfx, cbps);
	setIndexBuffer(gfx, indices);
	setPixelShader(gfx, pixelShader);
	setRasterizer(gfx);
	setTopology(gfx, topology);
	setVertexBuffer(gfx, vertices);
	setVertexShaderAndIA(gfx, vertexShader, idesc);
	setViewport(gfx);
}

void Cube::updateTransform(Graphics& gfx, float angle)
{
	const std::vector<ConstantBuffer> cbvs =
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

	setVSConstantBuffer(gfx, cbvs);
}
