#pragma once
#include "ICamera.h"
#include "FirstPersonCamera.h"
#include "World.h"
#include "RayIntersectionHelper.h"


enum Movement { LEFT, RIGHT, FWD, BACK, UP, DOWN };


class Player
{
private:
	float MovementSpeed;
	float MouseSensitivity;
	ICamera* camera;

public:
	Player();

	Player(ICamera* cam);

	ICamera* GetCamera();

	void HandlePlayerMovement(Movement direction, float DeltaTime);

	void ProcessMouseMovement(float, float, GLboolean);

	void HandlePlayerInput(World* world, GLFWwindow* window, int button, int action, int mods);
};