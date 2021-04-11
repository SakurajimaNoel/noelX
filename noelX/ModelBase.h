#pragma once
#include "Graphics.h"

class ModelBase 
{

	public:
	void setVSConstantBuffer(Graphics& gfx, float angle);
	void setPSConstantBuffer(Graphics& gfx);
	void setVertexBuffer(Graphics& gfx);
	void setIndexBuffer(Graphics& gfx);
	void setPixelShader(Graphics& gfx);
	void setVertexShaderAndIA(Graphics& gfx);
	void setRasterizer(Graphics& gfx);
	void setTopology(Graphics& gfx);
	void setViewport(Graphics& gfx);
};