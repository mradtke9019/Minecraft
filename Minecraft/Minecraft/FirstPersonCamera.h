#pragma once
#include "ICamera.h"
#include <iostream>

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

	enum Movement { LEFT, RIGHT, FWD, BACK };

	FirstPersonCamera();
	FirstPersonCamera(glm::vec3 position);
	~FirstPersonCamera();
	glm::mat4* GetViewTransform();
	void HandleKeyboardInput(FirstPersonCamera::Movement, float DeltaTime);
	void HandleMouseInput();
	void UpdateCameraVectors();
	void ProcessMouseMovement(float, float, GLboolean);

};