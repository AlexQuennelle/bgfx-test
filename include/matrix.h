#pragma once

#include "vectorN.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <format>
#include <iostream>
#include <numbers>

template <uint64_t W, uint64_t H = W> class Matrix
{
	public:
	Matrix() = default;
	~Matrix() = default;

	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;
	auto Transpose() const -> Matrix<H, W>
	{
		Matrix<H, W> newMat{};
		for (uint64_t x{0}; x < W; x++)
		{
			for (uint64_t y{0}; y < H; y++)
			{
				newMat[x, y] = (*this)[y, x];
			}
		}
		return newMat;
	}

	auto Data() const -> const float* { return this->data.data(); }
	static constexpr auto GetWidth() -> uint64_t { return W; }
	static constexpr auto GetHeight() -> uint64_t { return H; }

	void Print() const
	{
		std::array<std::string, H> lines;

		for (uint64_t y{0}; y < H; y++)
		{
			if (y == 0)
				lines[y].append(" 🭽");
			else if (y == H - 1)
				lines[y].append(" 🭼");
			else
				lines[y].append(" ▏");

			for (uint64_t x{0}; x < W; x++)
			{
				lines[y].append(std::format("{:.1f} ", (*this)[x, y]));
				if (x == W - 1)
				{
					lines[y].erase(lines[y].length() - 1);
					if (y == 0)
						lines[y].append("🭾");
					else if (y == H - 1)
						lines[y].append("🭿");
					else
						lines[y].append("▕");
				}
			}
			lines[y].append("\n");
		}

		std::string str{};
		for (auto line : lines)
		{
			str.append(line);
		}

		std::cout << str;
	}

	auto operator+(const Matrix<W, H>& other) -> Matrix<W, H>
	{
		Matrix<W, H> mat{};
		for (int x{0}; x < W; x++)
		{
			for (int y{0}; y < H; y++)
			{
				mat[x, y] = (*this)[x, y] + other[x, y];
			}
		}
		return mat;
	}
	auto operator-(const Matrix<W, H>& other) -> Matrix<W, H>
	{
		Matrix<W, H> mat{};
		for (int x{0}; x < W; x++)
		{
			for (int y{0}; y < H; y++)
			{
				mat[x, y] = (*this)[x, y] - other[x, y];
			}
		}
		return mat;
	}
	template <uint64_t W2>
	auto operator*(const Matrix<W2, W>& other) -> Matrix<W2, H>
	{
		Matrix<W2, H> mat{};
		for (uint64_t y{0}; y < H; y++)
		{
			for (uint64_t x{0}; x < W2; x++)
			{
				mat[x, y] = 0;
				for (int i{0}; i < W; i++)
				{
					mat[x, y] += (*this)[i, y] * other[x, i];
				}
			}
		}
		return mat;
	}

	auto operator=(const Matrix&) -> Matrix& = default;
	auto operator=(Matrix&&) -> Matrix& = default;
	auto operator[](const uint64_t x, const uint64_t y) const -> float
	{
		if (x >= W)
		{
			return 0;
		}
		if (y >= H)
		{
			return 0;
		}
		return data[(x * H) + y];
	}
	auto operator[](const uint64_t x, const uint64_t y) -> float&
	{
#ifndef NDEBUG
		assert(x < W);
		assert(y < H);
#endif // !NDEBUG

		return data[(x * H) + y];
	}

	private:
	std::array<float, W * H> data;
};
template <uint64_t N> class Matrix<N>
{
	public:
	Matrix() = default;
	~Matrix() = default;

	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;
	auto Transpose() const -> Matrix<N>
	{
		Matrix<N, N> newMat{};
		for (int x{0}; x < N; x++)
		{
			for (int y{0}; y < N; y++)
			{
				newMat[x, y] = (*this)[y, x];
			}
		}
		return newMat;
	}

	auto Data() const -> const float* { return this->data.data(); }
	static constexpr auto GetWidth() -> uint64_t { return N; }
	static constexpr auto GetHeight() -> uint64_t { return N; }

	void Print() const
	{
		std::array<std::string, N> lines;

		for (uint64_t y{0}; y < N; y++)
		{
			if (y == 0)
				lines[y].append(" 🭽");
			else if (y == N - 1)
				lines[y].append(" 🭼");
			else
				lines[y].append(" ▏");

			for (uint64_t x{0}; x < N; x++)
			{
				lines[y].append(std::format("{:.1f} ", (*this)[x, y]));
				if (x == N - 1)
				{
					lines[y].erase(lines[y].length() - 1);
					if (y == 0)
						lines[y].append("🭾");
					else if (y == N - 1)
						lines[y].append("🭿");
					else
						lines[y].append("▕");
				}
			}
			lines[y].append("\n");
		}

		std::string str{};
		for (auto line : lines)
		{
			str.append(line);
		}

		std::cout << str;
	}

	auto operator+(const Matrix<N>& other) -> Matrix<N>
	{
		Matrix<N> mat{};
		for (int x{0}; x < N; x++)
		{
			for (int y{0}; y < N; y++)
			{
				mat[x, y] = (*this)[x, y] + other[x, y];
			}
		}
		return mat;
	}
	auto operator-(const Matrix<N>& other) -> Matrix<N>
	{
		Matrix<N> mat{};
		for (int x{0}; x < N; x++)
		{
			for (int y{0}; y < N; y++)
			{
				mat[x, y] = (*this)[x, y] - other[x, y];
			}
		}
		return mat;
	}
	template <uint64_t W2>
	auto operator*(const Matrix<W2, N>& other) -> Matrix<W2, N>
	{
		Matrix<W2, N> mat{};
		for (uint64_t y{0}; y < N; y++)
		{
			for (uint64_t x{0}; x < W2; x++)
			{
				mat[x, y] = 0;
				for (int i{0}; i < N; i++)
				{
					mat[x, y] += (*this)[i, y] * other[x, i];
				}
			}
		}
		return mat;
	}

	auto operator=(const Matrix&) -> Matrix& = default;
	auto operator=(Matrix&&) -> Matrix& = default;
	auto operator[](const uint64_t x, const uint64_t y) const -> float
	{
		if (x >= N)
		{
			return 0;
		}
		if (y >= N)
		{
			return 0;
		}
		return data[(x * N) + y];
	}
	auto operator[](const uint64_t x, const uint64_t y) -> float&
	{
#ifndef NDEBUG
		assert(x < N);
		assert(y < N);
#endif // !NDEBUG

		return data[(x * N) + y];
	}

	static auto Identity() -> Matrix<N, N>
	{
		Matrix mat{};
		for (uint64_t i{0}; i < N; i++)
		{
			mat[i, i] = 1.0f;
		}
		return mat;
	}

	private:
	std::array<float, N * N> data;
};
template <> class Matrix<1, 3>
{
	public:
	Matrix() = default;
	~Matrix() = default;

	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;
	auto Transpose() const -> Matrix<3, 1>
	{
		Matrix<3, 1> newMat{};
		for (uint64_t y{0}; y < 3; y++)
		{
			newMat[0, y] = (*this)[y, 0];
		}
		return newMat;
	}

	auto Data() const -> const float* { return this->data.data(); }

	auto operator=(const Matrix&) -> Matrix& = default;
	auto operator=(Matrix&&) -> Matrix& = default;
	auto operator[](const uint64_t x, const uint64_t y) const -> float
	{
		if (x >= 1)
		{
			return 0;
		}
		if (y >= 3)
		{
			return 0;
		}
		return data[(x * 1) + y];
	}
	auto operator[](const uint64_t x, const uint64_t y) -> float&
	{
#ifndef NDEBUG
		assert(x < 1);
		assert(y < 3);
#endif // !NDEBUG

		return data[(x * 1) + y]; // NOLINT
	}
	explicit operator Vector3()
	{
		return {.x = (*this)[0, 0], .y = (*this)[0, 1], .z = (*this)[0, 2]};
	}

	private:
	std::array<float, 3> data;
};
template <> class Matrix<4>
{
	public:
	Matrix() = default;
	~Matrix() = default;

	Matrix(const Matrix<4>&) = default;
	Matrix(Matrix<4>&& other) noexcept : data(other.data)
	{
		other.data.fill(0.0f);
	}
	auto Transpose() const -> Matrix<4>
	{
		Matrix<4, 4> newMat{};
		for (uint64_t x{0}; x < 4; x++)
		{
			for (uint64_t y{0}; y < 4; y++)
			{
				newMat[x, y] = (*this)[y, x];
			}
		}
		return newMat;
	}
	auto Invert() const -> Matrix<4>
	{
		float b00
			= ((*this)[0, 0] * (*this)[1, 1]) - ((*this)[0, 1] * (*this)[1, 0]);
		float b01
			= ((*this)[0, 0] * (*this)[1, 2]) - ((*this)[0, 2] * (*this)[1, 0]);
		float b02
			= ((*this)[0, 0] * (*this)[1, 3]) - ((*this)[0, 3] * (*this)[1, 0]);
		float b03
			= ((*this)[0, 1] * (*this)[1, 2]) - ((*this)[0, 2] * (*this)[1, 1]);
		float b04
			= ((*this)[0, 1] * (*this)[1, 3]) - ((*this)[0, 3] * (*this)[1, 1]);
		float b05
			= ((*this)[0, 2] * (*this)[1, 3]) - ((*this)[0, 3] * (*this)[1, 2]);
		float b06
			= ((*this)[2, 0] * (*this)[3, 1]) - ((*this)[2, 1] * (*this)[3, 0]);
		float b07
			= ((*this)[3, 2] * (*this)[2, 0]) - ((*this)[2, 2] * (*this)[3, 0]);
		float b08
			= ((*this)[3, 3] * (*this)[2, 0]) - ((*this)[2, 3] * (*this)[3, 0]);
		float b09
			= ((*this)[2, 1] * (*this)[3, 2]) - ((*this)[2, 2] * (*this)[3, 1]);
		float b10
			= ((*this)[2, 1] * (*this)[3, 3]) - ((*this)[2, 3] * (*this)[3, 1]);
		float b11
			= ((*this)[2, 2] * (*this)[3, 3]) - ((*this)[2, 3] * (*this)[3, 2]);
		float invDet = 1.0f
					   / (b00
						  * b11
						  - b01
						  * b10
						  + b02
						  * b09
						  + b03
						  * b08
						  - b04
						  * b07
						  + b05
						  * b06);
		Matrix<4> result{};
		result[0, 0]
			= ((*this)[1, 1] * b11 - (*this)[1, 2] * b10 + (*this)[1, 3] * b09)
			  * invDet;
		result[0, 1]
			= (-(*this)[0, 1] * b11 + (*this)[0, 2] * b10 - (*this)[0, 3] * b09)
			  * invDet;
		result[0, 2]
			= ((*this)[3, 1] * b05 - (*this)[3, 2] * b04 + (*this)[3, 3] * b03)
			  * invDet;
		result[0, 3]
			= (-(*this)[2, 1] * b05 + (*this)[2, 2] * b04 - (*this)[2, 3] * b03)
			  * invDet;
		result[1, 0]
			= (-(*this)[1, 0] * b11 + (*this)[1, 2] * b08 - (*this)[1, 3] * b07)
			  * invDet;
		result[1, 1]
			= ((*this)[0, 0] * b11 - (*this)[0, 2] * b08 + (*this)[0, 3] * b07)
			  * invDet;
		result[1, 2]
			= (-(*this)[3, 0] * b05 + (*this)[3, 2] * b02 - (*this)[3, 3] * b01)
			  * invDet;
		result[1, 3]
			= ((*this)[2, 0] * b05 - (*this)[2, 2] * b02 + (*this)[2, 3] * b01)
			  * invDet;
		result[2, 0]
			= ((*this)[1, 0] * b10 - (*this)[1, 1] * b08 + (*this)[1, 3] * b06)
			  * invDet;
		result[2, 1]
			= (-(*this)[0, 0] * b10 + (*this)[0, 1] * b08 - (*this)[0, 3] * b06)
			  * invDet;
		result[2, 2]
			= ((*this)[3, 0] * b04 - (*this)[3, 1] * b02 + (*this)[3, 3] * b00)
			  * invDet;
		result[2, 3]
			= (-(*this)[2, 0] * b04 + (*this)[2, 1] * b02 - (*this)[2, 3] * b00)
			  * invDet;
		result[3, 0]
			= (-(*this)[1, 0] * b09 + (*this)[1, 1] * b07 - (*this)[1, 2] * b06)
			  * invDet;
		result[3, 1]
			= ((*this)[0, 0] * b09 - (*this)[0, 1] * b07 + (*this)[0, 2] * b06)
			  * invDet;
		result[3, 2]
			= (-(*this)[3, 0] * b03 + (*this)[3, 1] * b01 - (*this)[3, 2] * b00)
			  * invDet;
		result[3, 3]
			= ((*this)[2, 0] * b03 - (*this)[2, 1] * b01 + (*this)[2, 2] * b00)
			  * invDet;
		return result;
	}

	auto Data() const -> const float* { return this->data.data(); }
	static constexpr auto GetWidth() -> uint64_t { return 4; }
	static constexpr auto GetHeight() -> uint64_t { return 4; }

	void Print() const
	{
		std::array<std::string, 4> lines;

		for (uint64_t y{0}; y < 4; y++)
		{
			if (y == 0)
				lines[y].append(" 🭽");
			else if (y == 3)
				lines[y].append(" 🭼");
			else
				lines[y].append(" ▏");

			for (uint64_t x{0}; x < 4; x++)
			{
				lines[y].append(std::format("{:.1f} ", (*this)[x, y]));
				if (x == 3)
				{
					lines[y].erase(lines[y].length() - 1);
					if (y == 0)
						lines[y].append("🭾");
					else if (y == 3)
						lines[y].append("🭿");
					else
						lines[y].append("▕");
				}
			}
			lines[y].append("\n");
		}

		std::string str{};
		for (const auto& line : lines)
		{
			str.append(line);
		}

		std::cout << str;
	}

	auto operator+(const Matrix<4>& other) -> Matrix<4>
	{
		Matrix<4> mat{};
		for (uint64_t x{0}; x < 4; x++)
		{
			for (uint64_t y{0}; y < 4; y++)
			{
				mat[x, y] = (*this)[x, y] + other[x, y];
			}
		}
		return mat;
	}
	auto operator-(const Matrix<4>& other) -> Matrix<4>
	{
		Matrix<4> mat{};
		for (uint64_t x{0}; x < 4; x++)
		{
			for (uint64_t y{0}; y < 4; y++)
			{
				mat[x, y] = (*this)[x, y] - other[x, y];
			}
		}
		return mat;
	}
	template <uint64_t W2>
	auto operator*(const Matrix<W2, 4>& other) -> Matrix<W2, 4>
	{
		Matrix mat{};
		for (uint64_t y{0}; y < 4; y++)
		{
			for (uint64_t x{0}; x < W2; x++)
			{
				mat[x, y] = 0;
				for (int i{0}; i < 4; i++)
				{
					mat[x, y] += (*this)[i, y] * other[x, i];
				}
			}
		}
		return mat;
	}
	// auto operator*=(const Matrix<4>& other) -> Matrix<4>&
	// {
	// 	return *this;
	// }

	auto operator=(const Matrix<4>&) -> Matrix<4>& = default;
	auto operator=(Matrix<4>&& other) noexcept -> Matrix<4>&
	{
		this->data = other.data;
		other.data.fill(0.0f);
		return *this;
	}
	auto operator[](const uint64_t x, const uint64_t y) const -> float
	{
		if (x >= 4)
		{
			return 0;
		}
		if (y >= 4)
		{
			return 0;
		}
		return this->data[(x * 4) + y];
	}
	auto operator[](const uint64_t x, const uint64_t y) -> float&
	{
#ifndef NDEBUG
		assert(x < 4);
		assert(y < 4);
#endif // !NDEBUG

		return this->data[(x * 4) + y];
	}

	auto RotateY(const float angle, const bool degrees = true) const
		-> Matrix<4>
	{
		auto a{*this};
		return a * FromAngleY(angle, degrees);
	}
	static auto Identity() -> Matrix<4, 4>
	{
		Matrix mat{};
		for (uint64_t i{0}; i < 4; i++)
		{
			mat[i, i] = 1.0f;
		}
		return mat;
	}
	static auto FromBasis(const Normal3 x, const Normal3 y, const Normal3 z,
						  const Vector3 translation = {}) -> Matrix<4, 4>
	{
		Matrix result{};
		result[0, 0] = x.GetX();
		result[0, 1] = y.GetX();
		result[0, 2] = z.GetX();
		result[0, 3] = 0.0f;

		result[1, 0] = x.GetY();
		result[1, 1] = y.GetY();
		result[1, 2] = z.GetY();
		result[1, 3] = 0.0f;

		result[2, 0] = x.GetZ();
		result[2, 1] = y.GetZ();
		result[2, 2] = z.GetZ();
		result[2, 3] = 0.0f;

		result[3, 0] = -x.Dot(translation);
		result[3, 1] = -y.Dot(translation);
		result[3, 2] = -z.Dot(translation);
		result[3, 3] = 1.0f;

		return result;
	}
	static auto LookAt(const Vector3 eyePos, const Vector3 target,
					   const Normal3 upDir = Normal3::Up()) -> Matrix
	{
		const Normal3 forward{(target - eyePos).Normalize()};
		const Normal3 right{upDir.Cross(forward).Normalize()};
		const Normal3 up{forward.Cross(right).Normalize()}; // NOLINT

		return FromBasis(right, up, forward, eyePos);
	}
	static auto Projection(const float fovY, const float aspectRatio,
						   const float _near, const float _far,
						   const bool homogeneousNDC)
	{
		const float height{
			1.0f / std::tan(fovY * (std::numbers::pi_v<float> / 180.0f) * 0.5f),
		};
		const float width{height * (1.0f / aspectRatio)};
		const float depthRange{_far - _near};
		const float a{homogeneousNDC ? (_far + _near) / depthRange
									 : _far / depthRange};
		const float b{homogeneousNDC ? (2.0f * _far * _near) / depthRange
									 : _near * a};
		Matrix<4> result{};
		result[0, 0] = width;
		result[1, 1] = height;
		result[2, 0] = -0.0f;
		result[2, 1] = -0.0f;
		result[2, 2] = a;
		result[2, 3] = 1.0f;
		result[3, 2] = -b;
		return result;
	}
	static auto FromAngleY(const float angle, const bool degrees = true)
		-> Matrix<4>
	{
		float rads{degrees ? angle * (std::numbers::pi_v<float> / 180.0f)
						   : angle};
		Matrix result{};
		result[0, 0] = std::cos(rads);
		result[0, 2] = std::sin(rads);
		result[1, 1] = 1.0f;
		result[2, 0] = -std::sin(rads);
		result[2, 2] = std::cos(rads);
		result[3, 3] = 1.0f;

		return result;
	}

	private:
	std::array<float, 16> data;
};
