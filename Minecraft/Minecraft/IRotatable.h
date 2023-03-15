#include "glm/gtx/quaternion.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <exception>
#include "Log.h"

#pragma once
enum RotationType{Euler, AxisAngle};

/// <summary>
/// Interface representing a rotatable object. Uses radians for its angle representations.
/// </summary>
class IRotatable {
private:
	RotationType rotationType;
	float rotateX;
	float rotateY;
	float rotateZ;
	glm::vec3 Axis;
	float angle;


public:
	IRotatable()
	{
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;

		Axis = glm::vec3(0, 0, 0);
		angle = 0.0f;
		rotationType = Euler;
	}


	//Return angle clamped between 0 and 2 pi
	// https://www.ryanjuckett.com/cyclic-coordinate-descent-in-2d/
	static float SimplifyAngle(float angle)
	{
		angle = fmod(angle, (2.0 * M_PI));
		if (angle < -M_PI)
			angle += (2.0 * M_PI);
		else if (angle > M_PI)
			angle -= (2.0 * M_PI);
		return angle;
	}

	glm::mat4 GetRotationMatrix()
	{
		glm::mat4 result = glm::mat4(1);
		switch (rotationType)
		{
		case Euler:
			result =
				glm::rotate(result, *GetRotateY(), glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(result, *GetRotateZ(), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::rotate(result, *GetRotateX(), glm::vec3(1.0f, 0.0f, 0.0f));
			break;

		case AxisAngle:
			if (glm::length(Axis) <= 0 || Axis == glm::vec3(0, 0, 0))
			{
				Log::WriteLog("Axis angle using the 0 vector or the lenght of the axis is less than or equal to 0.", Warning);
				return glm::mat4(1);
			}

			result = glm::toMat4(glm::angleAxis(angle, Axis));
			break;

		default:
			Log::WriteLog("Rotation Method not found", Error);
			break;
		}
		return result;
	}


	bool GetRotationMethod()
	{
		return rotationType;
	}

	void SetRotationMethod(RotationType type)
	{
		rotationType = type;
	}

	float* GetRotateX()
	{
		return &rotateX;
	}

	float* GetRotateY()
	{
		return &rotateY;
	}
	float* GetRotateZ()
	{
		return &rotateZ;
	}

	void SetRotateX(float x)
	{
		rotateX = x;
	}

	void SetRotateY(float y)
	{
		rotateY = y;
	}

	void SetRotateZ(float z)
	{
		rotateZ = z;
	}

	void RotateX(float x)
	{
		rotateX += x;
	}

	void RotateY(float y)
	{
		rotateY += y;
	}

	void RotateZ(float z)
	{
		rotateZ += z;
	}

	void SetAxis(glm::vec3 a)
	{
		if (a == glm::vec3(0, 0, 0))
			Axis = -Axis;
		else
			Axis = glm::normalize(a);
	}

	void SetAxisAngle(float a)
	{
		angle = a;
	}

	void IncrementAxisAngle(float a)
	{
		angle += a;
	}

	float GetAxisAngle()
	{
		return angle;
	}

};