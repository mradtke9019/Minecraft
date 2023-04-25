#pragma once
#include "ICamera.h"
#include <iostream>
#include "Axis.h"


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

public:

	enum Movement { LEFT, RIGHT, FWD, BACK, UP, DOWN };

	FirstPersonCamera();
	FirstPersonCamera(glm::vec3 position);
	~FirstPersonCamera();
	glm::mat4* GetViewTransform();
	void HandleKeyboardInput(FirstPersonCamera::Movement, float DeltaTime);
	void UpdateCameraVectors();
	void ProcessMouseMovement(float, float, GLboolean);
	glm::vec3 GetCameraDirection();
};