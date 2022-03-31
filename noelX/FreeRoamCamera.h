#pragma once
#include "Graphics.h"



class FreeRoamCamera
{
public:
	FreeRoamCamera();
	DirectX::XMMATRIX getMatrix();
	void startCameraWindow();
	void reset();
	void cameraMoveForward();
	void cameraMoveBackward();
private:
	DirectX::XMFLOAT3 cameraPos;
	DirectX::XMFLOAT3 cameraForward;
	DirectX::XMFLOAT3 cameraUp;
	float cameraSpeed;
};