#include "FreeRoamCamera.h"
using namespace DirectX;
FreeRoamCamera::FreeRoamCamera()
{
	cameraPos = DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f);
	cameraUp = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	cameraForward = DirectX::XMFLOAT3(0.0f, 0.0f, 1.0f);
	cameraSpeed = 2.0f;
}

void FreeRoamCamera::startCameraWindow()
{
	if (ImGui::Begin("FreeRoamCamera"))
	{
		if (ImGui::Button("Forward"))
		{
			cameraMoveForward();
		}
		if (ImGui::Button("Backward"))
		{
			cameraMoveBackward();
		}
	}
	ImGui::End();
}

void FreeRoamCamera::cameraMoveForward()
{
	cameraPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void FreeRoamCamera::cameraMoveBackward()
{
	cameraPos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}