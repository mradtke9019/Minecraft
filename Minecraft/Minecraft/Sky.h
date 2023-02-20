#include <glm/glm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#pragma once
class Sky {
private:

public:

	// Accepts a time and converts it into a color that should be displayed for that time of day.
	// Utilizes a sinusoid to calculate the ratio between the night and day.
	static glm::vec3 GetColorForTimeOfDay(float currentTime, float dayDuration)
	{
		// Colors for night and day
		glm::vec3 night = glm::vec3(0.13f,0.176f,0.352f);
		glm::vec3 day = glm::vec3(0,0.749f,1.0f);
		

		// Ex: suppose day is 600 seconds. Time 0 is 100% dark, time 300 is 100% day. Time 600 is night again
		float period = (M_PI * 2) / dayDuration;
		float ratio = glm::abs(glm::sin(period * currentTime));
		// Ratio of 0 means use 100% of arg 1, Ratio of 1 means use all of arg 2
		return glm::mix(night, day, ratio);
	}
};