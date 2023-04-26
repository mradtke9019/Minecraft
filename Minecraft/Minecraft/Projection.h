#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

namespace Projection 
{
	static const float fovy = glm::radians(60.0f);
	static float Width = 1200;
	static float Height = 900;
	static float zNear = 0.1f;
	static float zFar = 300.0f;

	static glm::mat4 GetProjection()
	{
		return glm::perspective(glm::radians(60.0f), (float)Width / (float)Height, 0.1f, 300.0f);
	}
}