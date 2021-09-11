#include "PointLight.h"

void PointLight::startLightWindow()
{
	if (ImGui::Begin("Lighting"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -50.0f, 50.0f, "%.2f");
		ImGui::SliderFloat("Y", &pos.y, -50.0f, 50.0f, "%.01f");
		ImGui::SliderFloat("Z", &pos.z, -50.0f, 50.0f, "%.01f");
		if (ImGui::Button("Reset"))
		{
			reset();
		}
	}
	ImGui::End();
}

void PointLight::reset()
{
	pos = { 0.0f, 0.0f, 0.0f };
}

void PointLight::updateBuffer(Graphics& gfx)
{
	psBuff = { { DirectX::XMFLOAT3(pos.x,pos.y,pos.z) } };

	initPSConstantBuffer(gfx, psBuff);
}

