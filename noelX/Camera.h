#pragma once
#include "Graphics.h"

class Camera
{
public:
	Camera();
	DirectX::XMMATRIX getMatrix();
	void startCameraWindow();
	void reset();
private:
	float r;
	float theta;
	float phi;
	float yaw;
	float roll;
	float pitch;

	DirectX::XMFLOAT3 cameraPos;
	DirectX::XMFLOAT3 cameraTarget;
	DirectX::XMFLOAT3 cameraUp;
	DirectX::XMFLOAT3 direction;


};