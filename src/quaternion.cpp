#include "quaternion.h"

#include <cmath>

Quaternion::Quaternion(const Vector3D auto vec) :
	Quaternion(0.0f, vec.GetX(), vec.GetY(), vec.GetZ())
{ }
Quaternion::Quaternion(const float w, const float x, const float y,
					   const float z) :
	w(w), x(x), y(y), z(z)
{ }

auto Quaternion::GetW() const -> float { return this->w; }
auto Quaternion::GetX() const -> float { return this->x; }
auto Quaternion::GetY() const -> float { return this->y; }
auto Quaternion::GetZ() const -> float { return this->z; }

auto Quaternion::operator*(const Vector3D auto vec) const -> decltype(vec)
{
	Vector3 qVec{.x = this->x, .y = this->y, .z = this->z};
	Vector3 t{(qVec * 2.0f).Cross(vec)};
	Vector3 newVec{vec + (t * this->w) + qVec.Cross(t)};
	return static_cast<decltype(vec)>(newVec);
}

auto Quaternion::FromEulerAngle(const float x, const float y, const float z)
	-> Quaternion
{
	float cosX{std::cosf(x / 2.0f)};
	float cosY{std::cosf(y / 2.0f)};
	float cosZ{std::cosf(z / 2.0f)};
	float sinX{std::sinf(x / 2.0f)};
	float sinY{std::sinf(y / 2.0f)};
	float sinZ{std::sinf(z / 2.0f)};
	return {
		(cosX * cosY * cosZ) + (sinX * sinY * sinZ),
		(sinX * cosY * cosZ) - (cosX * sinY * sinZ),
		(cosX * sinY * cosZ) + (sinX * cosY * sinZ),
		(cosX * cosY * sinZ) - (sinX * sinY * cosZ),
	};
}
