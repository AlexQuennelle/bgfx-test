#include "vectorN.h"
#include "matrix.h"

#include <cmath>

auto Vector3::GetX() const -> float { return this->x; }
auto Vector3::GetY() const -> float { return this->y; }
auto Vector3::GetZ() const -> float { return this->z; }

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
auto Vector3::Normalize() const -> Normal3
{
	auto mag{this->Magnitude()};
	return {this->x / mag, this->y / mag, this->z / mag};
}
auto Vector3::Dot(const Vector3D auto other) const -> float
{
	return (this->x * other.GetX())
		   + (this->y * other.GetY())
		   + (this->z * other.GetZ());
}
auto Vector3::Angle(const Vector3D auto other) const -> float
{
	return std::acos(this->Dot(other)
					 / (this->Magnitude() * other.GetMagnitude()));
}
auto Vector3::Cross(const Vector3D auto other) const -> Vector3
{
	return {
		.x = (this->y * other.GetZ()) - (this->z * other.GetY()),
		.y = (this->z * other.GetX()) - (this->x * other.GetZ()),
		.z = (this->x * other.GetY()) - (this->y * other.GetX()),
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
Vector3::operator Matrix<1,4>()
{
	Matrix<1, 4> mat{};
	mat[0, 0] = this->x;
	mat[0, 1] = this->y;
	mat[0, 2] = this->z;
	mat[0, 3] = 1;
	return mat;
}

auto Vector3::operator+(const Vector3D auto other) const -> Vector3
{
	return {
		.x = this->x + other.GetX(),
		.y = this->y + other.GetY(),
		.z = this->z + other.GetZ(),
	};
}
auto Vector3::operator-(const Vector3D auto other) const -> Vector3
{
	return {
		.x = this->x - other.GetX(),
		.y = this->y - other.GetY(),
		.z = this->z - other.GetZ(),
	};
}
auto Vector3::operator*(const float value) const -> Vector3
{
	return {.x = this->x * value, .y = this->y * value, .z = this->z * value};
}
auto Vector3::operator/(const float value) const -> Vector3
{
	return {.x = this->x / value, .y = this->y / value, .z = this->z / value};
}

/******************************** Normal3 *************************************/

auto Normal3::GetX() const -> float { return this->x; }
auto Normal3::GetY() const -> float { return this->y; }
auto Normal3::GetZ() const -> float { return this->z; }

Normal3::operator Vector3()
{
	return {.x = this->x, .y = this->y, .z = this->z};
}
Normal3::operator Matrix<1, 3>()
{
	Matrix<1, 3> mat{};
	mat[0, 0] = this->x;
	mat[0, 1] = this->y;
	mat[0, 2] = this->z;
	return mat;
}
Normal3::operator Matrix<1,4>()
{
	Matrix<1, 4> mat{};
	mat[0, 0] = this->x;
	mat[0, 1] = this->y;
	mat[0, 2] = this->z;
	mat[0, 3] = 0;
	return mat;
}

auto Normal3::operator+(const Vector3D auto other) const -> Vector3
{
	return {
		.x = this->x + other.GetX(),
		.y = this->y + other.GetY(),
		.z = this->z + other.GetZ(),
	};
}
auto Normal3::operator-(const Vector3D auto other) const -> Vector3
{
	return {
		.x = this->x - other.GetX(),
		.y = this->y - other.GetY(),
		.z = this->z - other.GetZ(),
	};
}
auto Normal3::operator*(const float value) const -> Vector3
{
	return {.x = this->x * value, .y = this->y * value, .z = this->z * value};
}
auto Normal3::operator/(const float value) const -> Vector3
{
	return {.x = this->x / value, .y = this->y / value, .z = this->z / value};
}
