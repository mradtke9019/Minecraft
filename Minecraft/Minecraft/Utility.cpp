#include "Utility.h"

Utility::Utility()
{
	float DeltaTime = 0.0f;
	float LastFrame = 0.0f;
}

Utility::~Utility()
{
}

void Utility::Update(float TimePassed)
{
	float currentFrame = (TimePassed);
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;
}

float& Utility::GetDeltaTime()
{
	return DeltaTime;
}

