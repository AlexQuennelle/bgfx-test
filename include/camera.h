#pragma once

#include "matrix.h"

class Camera
{
	public:
	Camera() = default;

	void LookAt(const Vector3 target, const Normal3 upDir = Normal3::Up());

	private:
	Matrix<4> location;
};
