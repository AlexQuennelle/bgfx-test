#include "vector3.h"
#include "matrix.h"

#include <cmath>

auto Vector3::Magnitude() const -> float
{
	return std::sqrt(
		std::powf(this->x, 2) + std::powf(this->y, 2) + std::powf(this->z, 2));
}
auto Vector3::SquareMag() const -> float
{
	return std::powf(this->x, 2)
		   + std::powf(this->y, 2)
		   + std::powf(this->z, 2);
}
auto Vector3::Normalize() const -> Vector3
{
	auto mag{this->Magnitude()};
	return {.x = this->x / mag, .y = this->y / mag, .z = this->z / mag};
}
auto Vector3::Dot(const Vector3 other) const -> float
{
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

auto Vector3::Cross(const Vector3 other) const -> Vector3
{
	return {
		.x = (this->y * other.z) - (this->z * other.y),
		.y = (this->z * other.x) - (this->x * other.z),
		.z = (this->x * other.y) - (this->y * other.x),
	};
}

Vector3::operator Matrix<1, 3>()
{
	Matrix<1, 3> mat{};
	mat[0, 0] = this->x;
	mat[0, 1] = this->y;
	mat[0, 2] = this->z;
	return mat;
}
auto Vector3::Angle(const Vector3 other) const -> float
{
	return std::acos(this->Dot(other)
					 / (this->Magnitude() * other.Magnitude()));
}
