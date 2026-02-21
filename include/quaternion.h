#pragma once

#include "vectorN.h"

class Quaternion
{
	public:
	Quaternion(const Vector3D auto vec);
	Quaternion(const float w, const float x, const float y, const float z);

	auto GetW() const -> float;
	auto GetX() const -> float;
	auto GetY() const -> float;
	auto GetZ() const -> float;

	auto operator*(const Vector3D auto vec) const -> decltype(vec);

	static auto FromEulerAngle(const float x, const float y, const float z)
		-> Quaternion;

	private:
	float w;
	float x;
	float y;
	float z;
};
