#include "PointLight.h"

void PointLight::startLightWindow()
{
	if (ImGui::Begin("Lighting"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &lightCBuff.lightPos.x, -50.0f, 50.0f, "%.2f");
		ImGui::SliderFloat("Y", &lightCBuff.lightPos.y, -50.0f, 50.0f, "%.01f");
		ImGui::SliderFloat("Z", &lightCBuff.lightPos.z, -50.0f, 50.0f, "%.01f");
		
		ImGui::Text("Color");
		ImGui::ColorEdit3("Ambient", &lightCBuff.ambientLight.x);
		ImGui::ColorEdit3("Diffuse Color", &lightCBuff.diffuseColor.x);
		
		ImGui::Text("Intensity");
		ImGui::SliderFloat("Intensity", &lightCBuff.diffuseIntensity, 0.01f, 2.0f, "%.2f", ImGuiSliderFlags_Logarithmic );
		
		ImGui::Text("Attenuation");
		ImGui::SliderFloat("Constant", &lightCBuff.attConst, 0.05f, 10.0f, "%.2f", ImGuiSliderFlags_Logarithmic);
		ImGui::SliderFloat("Linear", &lightCBuff.attLin, 0.0001f, 4.0f, "%.4f", ImGuiSliderFlags_Logarithmic);
		ImGui::SliderFloat("Quadratic", &lightCBuff.attQuad, 0.0000001f, 10.0f, "%.7f", ImGuiSliderFlags_Logarithmic);

		if (ImGui::Button("Reset"))
		{
			reset();
		}
	}
	ImGui::End();
}

void PointLight::reset()
{
	//pos = { 0.0f, 0.0f, 0.0f };
	lightCBuff = {
		{0.0f,0.0f,0.0f},
		{ 0.05f, 0.05f, 0.05f },
		{ 1.0f, 1.0f, 1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f
	};
}

void PointLight::updateBuffer(Graphics& gfx, DirectX::XMMATRIX viewMatrix)
{
	//psBuff = { { DirectX::XMFLOAT3(pos.x,pos.y,pos.z) } };
	auto data = lightCBuff;
	const auto lPos = DirectX::XMLoadFloat3(&lightCBuff.lightPos);
	//DirectX::XMStoreFloat3(&data.lightPos, DirectX::XMVector3Transform(lPos, viewMatrix));
	initPSConstantBuffer(gfx, lightCBuff, 0u);
}

