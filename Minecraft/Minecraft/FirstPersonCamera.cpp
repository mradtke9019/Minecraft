#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera()
	:frustum()
{
	this->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	this->Front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->Up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->Right = glm::vec3();
	this->Target = glm::vec3(0.0f, 0.0f, 0.0f);
	this->View = glm::mat4(1.0f);
	UpdateCameraVectors();
}

FirstPersonCamera::FirstPersonCamera(glm::vec3 position)
	:frustum()
{
	this->SetPosition(position);
	this->Front = Axis::Z;
	this->Up = Axis::Y;
	this->Right = glm::vec3();
	this->Target = Axis::ZeroVector;
	this->View = glm::mat4(1.0f);
	UpdateCameraVectors();
}

glm::mat4* FirstPersonCamera::GetViewTransform()
{
	View = glm::lookAt(this->GetPosition(), GetPosition() + Front, Up);
	return &View;
}


void FirstPersonCamera::UpdateCameraVectors()
{
	//Direction = glm::normalize(Target - GetPosition());
	Front.x = glm::cos(GetRotateY()) * glm::cos(GetRotateX());
	Front.y = glm::sin(GetRotateX());
	Front.z = glm::sin(GetRotateY()) * glm::cos(GetRotateX());
	glm::vec3 worldUp = Axis::Y;
	Right = glm::normalize(glm::cross(Front, worldUp));
	//Should already be normalized by this point - redundant normalization, mostly safety check
	Up = glm::normalize(glm::cross(Right, Front));

	frustum.UpdateFrustum(this);
}


Frustum& FirstPersonCamera::GetFrustum()
{
	return frustum;
}


glm::vec3 FirstPersonCamera::GetCameraDirection()
{
	return Front;
}


glm::vec3 FirstPersonCamera::GetCameraRight()
{
	return Right;
}

glm::vec3 FirstPersonCamera::GetCameraUp()
{
	return Up;
}



FirstPersonCamera::~FirstPersonCamera()
{
	
}

