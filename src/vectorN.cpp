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

Vector3::operator Matrix<1, 3>()
{
	Matrix<1, 3> mat{};
	mat[0, 0] = this->x;
	mat[0, 1] = this->y;
	mat[0, 2] = this->z;
	return mat;
}
Vector3::operator Matrix<1, 4>()
{
	Matrix<1, 4> mat{};
	mat[0, 0] = this->x;
	mat[0, 1] = this->y;
	mat[0, 2] = this->z;
	mat[0, 3] = 1;
	return mat;
}
Vector3::operator bx::Vec3() { return {this->x, this->y, this->z}; }
Vector3::operator bx::Vec3() const { return {this->x, this->y, this->z}; }

auto Vector3::operator+() const -> Vector3 { return {*this}; }
auto Vector3::operator-() const -> Vector3
{
	return {.x = -this->x, .y = -this->y, .z = -this->z};
}

/******************************** Normal3 *************************************/

auto Normal3::GetX() const -> float { return this->x; }
auto Normal3::GetY() const -> float { return this->y; }
auto Normal3::GetZ() const -> float { return this->z; }

auto Normal3::Magnitude() -> float { return 1.0f; }
auto Normal3::SquareMag() -> float { return 1.0f; }
auto Normal3::Normalize() const -> Normal3 { return {*this}; }

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
Normal3::operator Matrix<1, 4>()
{
	Matrix<1, 4> mat{};
	mat[0, 0] = this->x;
	mat[0, 1] = this->y;
	mat[0, 2] = this->z;
	mat[0, 3] = 0;
	return mat;
}

auto Normal3::operator+() const -> Normal3 { return {*this}; }
auto Normal3::operator-() const -> Normal3
{
	return {-this->x, -this->y, -this->z};
}
