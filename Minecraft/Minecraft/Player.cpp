#include "Player.h"

Player::Player()
{
	camera = new FirstPersonCamera(glm::vec3(0.0f, 0.0f, -5.0f));
	this->MovementSpeed = 7.5f;
	this->MouseSensitivity = 0.00125f;
}

Player::Player(ICamera* cam)
{
	camera = cam;
	this->MovementSpeed = 7.5f;
	this->MouseSensitivity = 0.00125f;
}

ICamera* Player::GetCamera()
{
	return camera;
}

void Player::HandlePlayerMovement(Movement direction, float DeltaTime)
{
	glm::vec3 currPosition = camera->GetPosition();
	float velocity = MovementSpeed * DeltaTime;
	glm::vec3 front = camera->GetCameraDirection();
	glm::vec3 right = camera->GetCameraRight();

	if (direction == BACK)
	{
		currPosition -= front * velocity;
	}
	else if (direction == FWD) 
	{
		currPosition += front * velocity;
	}
	else if (direction == LEFT) 
	{
		currPosition -= right * velocity;
	}
	else if (direction == RIGHT) 
	{
		currPosition += right * velocity;
	}
	else if (direction == UP)
	{
		currPosition += Axis::Y * velocity;
	}
	else if (direction == DOWN)
	{
		currPosition -= Axis::Y * velocity;
	}
	camera->SetPosition(currPosition);

	//frustum.UpdateFrustum(this);
}


void Player::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	camera->RotateY(xoffset);
	camera->RotateX(yoffset);

	float constrain = 89.0f * (M_PI / 180.0f);

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (camera->GetRotateX() > constrain) {
			camera->SetRotateX(constrain);
		}

		if (camera->GetRotateX() < -constrain) {
			camera->SetRotateX(-constrain);
		}

	}

	// update Front, Right and Up Vectors using the updated Euler angles
	camera->UpdateCameraVectors();
}

void Player::HandlePlayerInput(World* world, GLFWwindow* window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		Log::WriteLog("Left mouse click", Info);

		glm::vec3 rayOrigin = GetCamera()->GetPosition();
		glm::vec3 rayDirection = GetCamera()->GetCameraDirection();
		Block* closest = nullptr;

		float closestDistance = std::numeric_limits<float>::max();
		std::vector<Chunk>* chunks = world->GetChunks();
		// Check for intersection with each triangle in the model
		for (int i = 0; i < chunks->size(); i++)
		{
			std::vector<Block*> blocks = chunks->at(i).GetBlocks();
			for (auto block : blocks)
			{
				if (!block->IsVisible())
				{
					continue;
				}
				RayIntersectionResult r = RayIntersectionHelper::IsRayIntersectingCube(rayOrigin, rayDirection, block->GetPosition(), 1.0f);

				if (r.IsIntersecting && r.Distance < closestDistance)
				{
					closest = block;
					closestDistance = r.Distance;

				}
			}
		}

		if (closest != nullptr)
		{
			world->GetWorldDelta()->AddOrModifyDelta(closest->GetPosition(), BlockType::None);
			closest->SetVisibility(false);
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		Log::WriteLog("Right mouse click", Info);

		glm::vec3 rayOrigin = GetCamera()->GetPosition();
		glm::vec3 rayDirection = GetCamera()->GetCameraDirection();

		std::vector<BlockIntersectionResult> hits = std::vector<BlockIntersectionResult>();

		std::vector<Chunk>* chunks = world->GetChunks();

		// Find all intersecting blocks both visible and invisible
		for (int i = 0; i < chunks->size(); i++)
		{
			std::vector<Block*> blocks = chunks->at(i).GetBlocks();
			for (auto block : blocks)
			{
				RayIntersectionResult r = RayIntersectionHelper::IsRayIntersectingCube(rayOrigin, rayDirection, block->GetPosition(), 1.0f);

				if (r.IsIntersecting)
				{
					BlockIntersectionResult br = BlockIntersectionResult();
					br.Distance = r.Distance;
					br.block = block;
					br.IsIntersecting = true;
					hits.push_back(br);
				}
			}
		}

		// Search our hits for the closest visible object. The next closest invisible object will be the one we want to make visible
		bool foundVisible = false;
		std::sort(hits.begin(), hits.end());
		for (int i = 1; i < hits.size(); i++)
		{
			if (hits[i].block->IsVisible())
			{
				foundVisible = true;
			}
			if (foundVisible)
			{
				Block* block = hits[i - 1].block;
				world->GetWorldDelta()->AddOrModifyDelta(block->GetPosition(), BlockType::Grass);
				block->SetVisibility(true);
				return;
			}
		}
	}
}
