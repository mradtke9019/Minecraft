#pragma once
#include "ICamera.h"
#include <iostream>
#include "Axis.h"
#include "Frustum.h"

class FirstPersonCamera : public ICamera
{
private:
	glm::vec3 Front;
	glm::vec3 Direction;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 Target;
	glm::mat4 View;
	float MovementSpeed;
	float MouseSensitivity;
	Frustum frustum;

public:

	enum Movement { LEFT, RIGHT, FWD, BACK, UP, DOWN };

	FirstPersonCamera();
	FirstPersonCamera(glm::vec3 position);
	~FirstPersonCamera();
	glm::mat4* GetViewTransform();
	void HandleKeyboardInput(FirstPersonCamera::Movement, float DeltaTime);
	void UpdateCameraVectors();
	void ProcessMouseMovement(float, float, GLboolean);
	Frustum& GetFrustum();
	glm::vec3 GetCameraDirection();
	glm::vec3 GetCameraRight();
	glm::vec3 GetCameraUp();
};