#pragma once
#include "ICamera.h"
#include <iostream>

class ThirdPersonCamera : public ICamera
{
private:
	float DistanceFromPlayer;
	float AngleAroundPlayer;

public:

	enum Movement { LEFT, RIGHT, FWD, BACK };

	ThirdPersonCamera();
	ThirdPersonCamera(glm::vec3 position);
	~ThirdPersonCamera();
	glm::mat4* GetViewTransform();
	void HandleKeyboardInput(ThirdPersonCamera::Movement, float DeltaTime);
	void UpdateCameraVectors();
	void ProcessMouseMovement(float, float, GLboolean);

};