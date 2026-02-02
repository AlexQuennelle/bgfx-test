#pragma once

#include <cstdint>

template <uint64_t, uint64_t> class Matrix;

struct Vector3
{
	float x{0};
	float y{0};
	float z{0};

	auto Magnitude() const -> float;
	auto SquareMag() const -> float;
	auto Normalize() const -> Vector3;
	auto Dot(const Vector3 other) const -> float;
	auto Angle(const Vector3 other) const -> float;
	auto Cross(const Vector3 other) const -> Vector3;

	explicit operator Matrix<1, 3>();
};
