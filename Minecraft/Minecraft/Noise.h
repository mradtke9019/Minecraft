
#pragma once
#include "Constants.h"
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

	/// <summary>
	/// Accepts a vec2 and returns a deterministic random value
	/// </summary>
	static float DeterministicRand(glm::vec2 v)
	{
		return glm::fract(sin(glm::dot(v,  glm::vec2(12.9898, 78.233))) * 43758.5453123);
	}


	static float noise(glm::vec2 st) {
		glm::vec2 i = floor(st);
		glm::vec2 f = fract(st);

		// Four corners in 2D of a tile
		float a = DeterministicRand(i);
		float b = DeterministicRand(i + glm::vec2(1, 0.0));
		float c = DeterministicRand(i + glm::vec2(0.0, 1.0));
		float d = DeterministicRand(i + glm::vec2(1.0, 1.0));

		// Smooth Interpolation

		// Cubic Hermine Curve.  Same as SmoothStep()
		glm::vec2 u = f * f * (3.0f - 2.0f * f);
		// u = smoothstep(0.,1.,f);
		// Mix 4 coorners percentages
		return glm::mix(a, b, u.x) +
			(c - a) * u.y * (1.0 - u.x) +
			(d - b) * u.x * u.y;
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
		glm::vec2 coord = chunkCoordinate + (blockCoordinate / float(Constants::CHUNK_SIZE));

		float n = noise(coord);// *max;
		return n * max; // Scale noise to max height


		float result = static_cast <float> (rand() / static_cast <float> (RAND_MAX));
		return result;
	}
};