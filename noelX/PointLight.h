#pragma once
#include "ModelBase.h"

class PointLight : public ModelBase
{
public:
	void startLightWindow();
	void reset();
	void updateBuffer(Graphics& gfx, DirectX::XMMATRIX viewMatrix);
	//DirectX::XMFLOAT3 lightPos = { 0.0f, 0.0f, 0.0f };
private:
	struct lightConstBuff
	{
		alignas(16) DirectX::XMFLOAT3 lightPos;
		alignas(16) DirectX::XMFLOAT3 ambientLight;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};
	//std::vector<lightConstBuff> psBuff;
	lightConstBuff lightCBuff = { 
		{0.0f,0.0f,0.0f},
		{ 0.05f, 0.05f, 0.05f },
		{ 1.0f, 1.0f, 1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f 
	};
};