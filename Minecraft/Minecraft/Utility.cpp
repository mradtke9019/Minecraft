#include "Utility.h"

Utility::Utility()
{
	DeltaTime = 0.0f;
	LastFrame = 0.0f;
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

