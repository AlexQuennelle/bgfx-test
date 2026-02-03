#pragma once

#include <cstdint>
#include <type_traits>

template <uint64_t, uint64_t> class Matrix;

struct Vector3;
class Normal3;
template <typename T>
concept Vector3D = std::is_same_v<T, Vector3> || std::is_same_v<T, Normal3>;

struct Vector3
{
	float x{0};
	float y{0};
	float z{0};

	auto GetX() const -> float;
	auto GetY() const -> float;
	auto GetZ() const -> float;

	auto Magnitude() const -> float;
	auto SquareMag() const -> float;
	auto Normalize() const -> Normal3;
	auto Dot(const Vector3D auto other) const -> float;
	auto Angle(const Vector3D auto other) const -> float;
	auto Cross(const Vector3D auto other) const -> Vector3;

	explicit operator Matrix<1, 3>();
	explicit operator Matrix<1, 4>();

	auto operator+(const Vector3D auto other) const -> Vector3;
	auto operator-(const Vector3D auto other) const -> Vector3;
	auto operator*(const float value) const -> Vector3;
	auto operator/(const float value) const -> Vector3;
};

class Normal3
{
	public:
	auto GetX() const -> float;
	auto GetY() const -> float;
	auto GetZ() const -> float;

	private:
	Normal3() = default;
	Normal3(const float x, const float y, const float z) : x(x), y(y), z(z) { };

	friend auto Vector3::Normalize() const -> Normal3;

	explicit operator Vector3();
	explicit operator Matrix<1, 3>();
	explicit operator Matrix<1, 4>();

	auto operator+(const Vector3D auto other) const -> Vector3;
	auto operator-(const Vector3D auto other) const -> Vector3;
	auto operator*(const float value) const -> Vector3;
	auto operator/(const float value) const -> Vector3;

	float x{0};
	float y{0};
	float z{0};
};
