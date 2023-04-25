
#pragma once
#include <glm/glm.hpp>
#include <random>

class Noise {
private:
	// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
	static int random(int seed, int min, int max) //range : [min, max]
	{
		static bool first = true;
		if (first)
		{
			srand(seed); //seeding for the first time only!
			first = false;
		}
		return min + rand() % ((max + 1) - min);
	}

public:

	/// <summary>
	/// Given a seed, a chunk coordinate, and local block coordinate, calculate what the highest block should be in that position using
	/// some sort of noise function
	/// </summary>
	static int GenerateHeight(int seed, int min, int max, glm::vec2 chunkCoordinate, glm::vec2 blockCoordinate)
	{
		static bool first = true;
		if (first)
		{
			srand(seed); //seeding for the first time only!
			first = false;
		}

		return random(seed, min, max);
		float result = static_cast <float> (rand() / static_cast <float> (RAND_MAX));

		return result;
	}
};