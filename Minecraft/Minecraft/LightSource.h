#include <glm/glm.hpp>

#pragma once
/// <summary>
/// Class describing a 
/// </summary>
class LightSource  {
private:
	glm::vec3 LightPosition;
	glm::vec3 LightColor;

public:

	LightSource();

	/// <summary>
	/// Initialize a light source with a position and a color.
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="color"></param>
	LightSource(glm::vec3 pos, glm::vec3 color);

	glm::vec3 GetLightPosition();

	void SetLightPosition(glm::vec3 pos);

	glm::vec3 GetLightColor();

	void SetLightColor(glm::vec3 col);
};