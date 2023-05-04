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
	Frustum frustum;

public:

	FirstPersonCamera();
	FirstPersonCamera(glm::vec3 position);
	~FirstPersonCamera();
	glm::mat4* GetViewTransform();
	void UpdateCameraVectors();
	Frustum& GetFrustum();
	glm::vec3 GetCameraDirection();
	glm::vec3 GetCameraRight();
	glm::vec3 GetCameraUp();
};