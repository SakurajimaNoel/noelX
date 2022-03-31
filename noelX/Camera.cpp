#include "Camera.h"

Camera::Camera()
{
	r = 2.5f;
	theta = 0.0f;
	phi = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
	pitch = 0.0f;

	/*cameraPos = DirectX::XMFLOAT3(0.0f, 0.0f, -1.0f);
	cameraTarget = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	cameraUp = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	direction = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);*/
}




void Camera::reset()
{
	r = 2.5f;
	theta = 0.0f;
	phi = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
	pitch = 0.0f;
}

void Camera::startCameraWindow()
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::SliderFloat("Radial Distance", &r, 1.0f, 80.0f, "%.1f");
		ImGui::SliderAngle("Polar Angle", &theta, -180.0f, 180.0f);
		ImGui::SliderAngle("Azimuthal Angle", &phi, -89.0f, 89.0f);
		ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
		if(ImGui::Button("Reset"))
		{
			reset();
		}
	}
	ImGui::End();
}

DirectX::XMMATRIX Camera::getMatrix()
{
	//returns the view matrix
	const auto position = DirectX::XMVector3Transform(DirectX::XMVectorSet(0.0f, 0.0f, r, 0.0f), DirectX::XMMatrixRotationRollPitchYaw(phi, -theta, 0.0f));
	return DirectX::XMMatrixLookAtLH(position,
		DirectX::XMVectorZero(),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f))*
		DirectX::XMMatrixRotationRollPitchYaw(pitch, -yaw, roll);
	//return DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&cameraPos), DirectX::XMLoadFloat3(&cameraTarget), DirectX::XMLoadFloat3(&cameraUp));
}