#include "ITranslatable.h"
#include "IRotatable.h"

#pragma once

class ITransformable : public ITranslatable, public IRotatable {
private:
	glm::mat4 transform;
public:
	ITransformable()
		: ITranslatable(), IRotatable()
	{
		transform = GetTranslationMatrix() * GetRotationMatrix();
	}

	void SetPosition(glm::vec3 p)
	{
		ITranslatable::SetPosition(p);
		transform = GetTranslationMatrix() * GetRotationMatrix();
	}

	void SetRotateX(float x)
	{
		IRotatable::SetRotateX(x); 
		transform = GetTranslationMatrix() * GetRotationMatrix();
	}

	void SetRotateY(float y)
	{
		IRotatable::SetRotateY(y);
		transform = GetTranslationMatrix() * GetRotationMatrix();
	}

	void SetRotateZ(float z)
	{
		IRotatable::SetRotateZ(z);
		transform = GetTranslationMatrix() * GetRotationMatrix();
	}

	void RotateX(float x)
	{
		IRotatable::RotateX(x);
		transform = GetTranslationMatrix() * GetRotationMatrix();
	}

	void RotateY(float y)
	{
		IRotatable::RotateY(y);
		transform = GetTranslationMatrix() * GetRotationMatrix();
	}

	void RotateZ(float z)
	{
		IRotatable::RotateZ(z);
		transform = GetTranslationMatrix() * GetRotationMatrix();
	}


	glm::mat4 GetTransform()
	{
		return transform;
	}

	glm::mat4* GetTransformPointer()
	{
		return &transform;
	}
};