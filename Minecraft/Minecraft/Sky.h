#include <glm/glm.hpp>


#pragma once
class Sky {
private:

public:

	// Accepts a time and converts it into a color that should be displayed for that time of day.
	// Utilizes a sinusoid to 
	static glm::vec3 GetColorForTimeOfDay(float currentTime, float dayDuration)
	{
		glm::vec3 start = glm::vec3(0, 0, 0);
		glm::vec3 end = glm::vec3(1, 1, 1);
		int currTime = static_cast<int>(currentTime);
		int dayDuration = static_cast<int>(dayDuration);
		// Ex: suppose day is 600 seconds. Time 0 is 100% dark, time 300 is 100% day.

		float ratio = 0.5;

		return glm::mix(start, end, ratio);
	}
};