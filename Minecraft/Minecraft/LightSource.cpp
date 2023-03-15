#include "LightSource.h"


LightSource::LightSource()
{
	LightPosition = glm::vec3(0, 0, 0);
	// Default to red to visually show that light is not initilized.
	LightColor = glm::vec3(1, 0, 0);
}

LightSource::LightSource(glm::vec3 pos, glm::vec3 color)
{
	LightPosition = pos;
	LightColor = color;
}

glm::vec3 LightSource::GetLightPosition()
{
	return LightPosition;
}

void LightSource::SetLightPosition(glm::vec3 pos)
{
	LightPosition = pos;
}