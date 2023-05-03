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
	glm::mat4 RotationMatrix;
	/// <summary>
	/// The rotation method to be used by this object such as using euler angles or the axis angle method.
	/// </summary>
	RotationType rotationType;
	/// <summary>
	/// The angle in radians in which we will rotate about the x axis.
	/// </summary>
	float rotateX;
	/// <summary>
	/// The angle in radians in which we will rotate about the y axis.
	/// </summary>
	float rotateY;
	/// <summary>
	/// The angle in radians in which we will rotate about the z axis.
	/// </summary>
	float rotateZ;

	/// <summary>
	/// The point in which the rotation will happen about.
	/// </summary>
	glm::vec3 pivot;

	/// <summary>
	/// The axis in which we will rotate about in  the axis angle representation;
	/// </summary>
	glm::vec3 Axis;
	/// <summary>
	/// The angle in radians in which we will rotate about the axis specified.
	/// </summary>
	float angle;

	void UpdateRotationMatrix()
	{
		glm::mat4 result = glm::mat4(1);
		switch (rotationType)
		{
		case Euler:
			result =
				glm::rotate(result, GetRotateY(), glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(result, GetRotateZ(), glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::rotate(result, GetRotateX(), glm::vec3(1.0f, 0.0f, 0.0f));
			break;

		case AxisAngle:
			if (glm::length(Axis) <= 0 || Axis == glm::vec3(0, 0, 0))
			{
				Log::WriteLog("Axis angle using the 0 vector or the length of the axis is less than or equal to 0.", Warning);
				RotationMatrix = glm::mat4(1);
				return;
			}

			result = glm::toMat4(glm::angleAxis(angle, Axis));
			break;

		default:
			Log::WriteLog("Rotation Method not found", Error);
			break;
		}
		if (pivot == glm::vec3(0))
		{
			RotationMatrix = result;
			return;
		}

		RotationMatrix = glm::translate(glm::mat4(1), pivot) * result * glm::translate(glm::mat4(1), -pivot);
	}


public:
	IRotatable()
	{
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;

		pivot = glm::vec3(0, 0, 0);
		Axis = glm::vec3(0, 0, 0);
		angle = 0.0f;
		rotationType = Euler;
		UpdateRotationMatrix();
	}

	/// <summary>
	/// Returns the rotation matrix about a pivot and the currently chosen rotation type.
	/// </summary>
	/// <returns></returns>
	glm::mat4 GetRotationMatrix()
	{
		return RotationMatrix;
	}

	void SetPivot(glm::vec3 p)
	{
		pivot = p;
		UpdateRotationMatrix();
	}

	glm::vec3 GetPivot()
	{
		return pivot;
	}

	bool GetRotationMethod()
	{
		return rotationType;
	}

	void SetRotationMethod(RotationType type)
	{
		rotationType = type;
		UpdateRotationMatrix();
	}

	float& GetRotateX()
	{
		return rotateX;
	}

	float& GetRotateY()
	{
		return rotateY;
	}
	float& GetRotateZ()
	{
		return rotateZ;
	}

	void SetRotateX(float x)
	{
		rotateX = x;
		UpdateRotationMatrix();
	}

	void SetRotateY(float y)
	{
		rotateY = y;
		UpdateRotationMatrix();
	}

	void SetRotateZ(float z)
	{
		rotateZ = z;
		UpdateRotationMatrix();
	}

	void RotateX(float x)
	{
		rotateX += x;
		UpdateRotationMatrix();
	}

	void RotateY(float y)
	{
		rotateY += y;
		UpdateRotationMatrix();
	}

	void RotateZ(float z)
	{
		rotateZ += z;
		UpdateRotationMatrix();
	}

	void SetAxis(glm::vec3 a)
	{
		if (a == glm::vec3(0, 0, 0))
			Axis = -Axis;
		else
			Axis = glm::normalize(a);
		UpdateRotationMatrix();
	}

	void SetAxisAngle(float a)
	{
		angle = a;
		UpdateRotationMatrix();
	}

	void IncrementAxisAngle(float a)
	{
		angle += a;
		UpdateRotationMatrix();
	}

	float GetAxisAngle()
	{
		return angle;
	}

};