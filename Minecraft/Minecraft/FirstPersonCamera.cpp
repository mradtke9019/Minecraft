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

	this->MovementSpeed = 2.5f;
	this->MouseSensitivity = 0.001f;
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

	this->MovementSpeed = 7.5f;
	this->MouseSensitivity = 0.00125f;
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

void FirstPersonCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	RotateY(xoffset);
	RotateX(yoffset);

	float constrain = 89.0f * (M_PI / 180.0f);

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (GetRotateX() > constrain) {
			SetRotateX(constrain);
		}

		if (GetRotateX() < -constrain) {
			SetRotateX(-constrain);
		}

	}

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
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

void FirstPersonCamera::HandleKeyboardInput(FirstPersonCamera::Movement direction, float DeltaTime) {
	
	float velocity = MovementSpeed * DeltaTime;

	if (direction == FirstPersonCamera::BACK) 
	{
		glm::vec3 currPosition = GetPosition();
		currPosition -= Front * velocity;
		SetPosition(currPosition);
	}
	else if (direction == FirstPersonCamera::FWD) {
		glm::vec3 currPosition = GetPosition();
		currPosition += Front * velocity;
		SetPosition(currPosition);
	}
	else if (direction == FirstPersonCamera::LEFT) {
		glm::vec3 currPosition = GetPosition();
		currPosition -= Right * velocity;
		SetPosition(currPosition);
	}
	else if (direction == FirstPersonCamera::RIGHT) {
		glm::vec3 currPosition = GetPosition();
		currPosition += Right * velocity;
		SetPosition(currPosition);
	}
	else if (direction == FirstPersonCamera::UP)
	{

		glm::vec3 currPosition = GetPosition();
		currPosition += Axis::Y * velocity;
		SetPosition(currPosition);
	}
	else if (direction == FirstPersonCamera::DOWN)
	{

		glm::vec3 currPosition = GetPosition();
		currPosition -= Axis::Y * velocity;
		SetPosition(currPosition);
	}

	frustum.UpdateFrustum(this);
}


FirstPersonCamera::~FirstPersonCamera()
{
	
}

