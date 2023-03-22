#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera()
{
	this->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	this->Front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	this->Up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->Right = glm::vec3();
	this->Target = glm::vec3(0.0f, 0.0f, 0.0f);
	this->View = glm::mat4(1.0f);
	UpdateCameraVectors();

	this->MovementSpeed = 2.5f;
	this->MouseSensitivity = 0.01f;
}

FirstPersonCamera::FirstPersonCamera(glm::vec3 position)
{
	this->SetPosition(position);
	this->Front = glm::vec3(0.0f, 0.0f, 1.0f);
	this->Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	this->Up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->Right = glm::vec3();
	this->Target = glm::vec3(0.0f, 0.0f, 0.0f);
	this->View = glm::mat4(1.0f);
	UpdateCameraVectors();

	this->MovementSpeed = 2.5f;
	this->MouseSensitivity = 0.01f;
}

glm::mat4* FirstPersonCamera::GetViewTransform()
{
	View = glm::lookAt(this->GetPosition(), GetPosition() + Front, Up);
	return &View;
	
}


void FirstPersonCamera::UpdateCameraVectors()
{
	//Direction = glm::normalize(Target - GetPosition());
	Front.x = glm::cos(*GetRotateY()) * glm::cos(*GetRotateX());
	Front.y = glm::cos(*GetRotateX());
	Front.z = glm::sin(*GetRotateY()) * glm::sin(*GetRotateX());
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Right = glm::normalize(glm::cross(Front, worldUp));
	//Should already be normalized by this point - redundant normalization, mostly safety check
	Up = glm::normalize(glm::cross(Right, Front));

}

void FirstPersonCamera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	RotateY(xoffset);
	RotateX(yoffset);

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (*GetRotateX() > 1.553f)
			SetRotateX(1.553f);
		if (*GetRotateY() < -1.553f)
			SetRotateY(-1.553f);
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}


void FirstPersonCamera::HandleKeyboardInput(FirstPersonCamera::Movement direction, float DeltaTime) {
	
	float velocity = MovementSpeed * DeltaTime;

	if (direction == FirstPersonCamera::BACK) 
	{
		glm::vec3 currPosition = GetPosition();
		currPosition -= Front * velocity;
		SetPosition(currPosition);
	}
	if (direction == FirstPersonCamera::FWD) {
		glm::vec3 currPosition = GetPosition();
		currPosition += Front * velocity;
		SetPosition(currPosition);
	}
	if (direction == FirstPersonCamera::LEFT) {
		glm::vec3 currPosition = GetPosition();
		currPosition -= Right * velocity;
		SetPosition(currPosition);
	}
	if (direction == FirstPersonCamera::RIGHT) {
		glm::vec3 currPosition = GetPosition();
		currPosition += Right * velocity;
		SetPosition(currPosition);
	}
}

void FirstPersonCamera::HandleMouseInput()
{

}


FirstPersonCamera::~FirstPersonCamera()
{
	
}

