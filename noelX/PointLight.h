#pragma once
#include "ModelBase.h"

class PointLight : public ModelBase
{
public:
	void startLightWindow();
	void reset();
	void updateBuffer(Graphics& gfx);
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
private:
	struct lightConstBuff
	{
		DirectX::XMFLOAT3 pos;
		float padding;
	};
	std::vector<lightConstBuff> psBuff = { { DirectX::XMFLOAT3(0.0f,0.0f,0.0f) } };
	
};