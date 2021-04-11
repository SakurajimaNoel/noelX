#include "Cube.h"

Cube::Cube(Graphics& gfx)
{
	setVSConstantBuffer(gfx,0.0f);
	setPSConstantBuffer(gfx);
	setIndexBuffer(gfx);
	setPixelShader(gfx);
	setRasterizer(gfx);
	setTopology(gfx);
	setVertexBuffer(gfx);
	setVertexShaderAndIA(gfx);
	setViewport(gfx);
}