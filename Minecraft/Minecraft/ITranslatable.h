
#pragma once
#include <glm/gtc/matrix_transform.hpp>

class ITranslatable {
private:
	glm::vec3 Position;
	glm::mat4 TranslationMatrix;
	void UpdateTranslationMatrix()
	{
		TranslationMatrix = glm::translate(glm::mat4(1), Position);
	}

public:
	ITranslatable()
	{
		Position = glm::vec3(0, 0, 0);
		glm::translate(glm::mat4(1), Position);
	}

	glm::mat4 GetTranslationMatrix()
	{
		return TranslationMatrix;
	}

	glm::vec3 GetPosition()
	{
		return Position;
	}

	void SetPosition(glm::vec3 p)
	{
		Position = p;
		UpdateTranslationMatrix();
	}
};