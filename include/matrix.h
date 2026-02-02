#pragma once

#include "vector3.h"

#include <array>
#include <cassert>
#include <cstdint>

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
		for (int x{0}; x < W; x++)
		{
			for (int y{0}; y < H; y++)
			{
				newMat[x, y] = (*this)[y, x];
			}
		}
		return newMat;
	}

	auto Data() const -> const float* { return this->data.data(); }

	auto operator=(const Matrix&) -> Matrix& = default;
	auto operator=(Matrix&&) -> Matrix& = default;
	auto operator[](const uint64_t x, const uint64_t y) const -> float
	{
		if (x < 0 || x >= W)
		{
			return 0;
		}
		if (y < 0 || y >= H)
		{
			return 0;
		}
		return data[(x * H) + y];
	}
	auto operator[](const uint64_t x, const uint64_t y) -> float&
	{
#ifndef NDEBUG
		assert(x >= 0 && x < W);
		assert(y >= 0 && y < H);
#endif // !NDEBUG

		return data[(x * H) + y];
	}

	private:
	std::array<float, W * H> data;
};
template <uint64_t N> class Matrix<N, N>
{
	public:
	Matrix() = default;
	~Matrix() = default;

	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;
	auto Transpose() const -> Matrix<N, N>
	{
		Matrix<N, N> newMat{};
		for (int x{0}; x < N; x++)
		{
			for (int y{0}; y < N; y++)
			{
				newMat[x, y] = this[y, x];
			}
		}
		return newMat;
	}

	auto Data() const -> const float* { return this->data.data(); }

	auto operator=(const Matrix&) -> Matrix& = default;
	auto operator=(Matrix&&) -> Matrix& = default;
	auto operator[](const uint64_t x, const uint64_t y) const -> float
	{
		if (x < 0 || x >= N)
		{
			return 0;
		}
		if (y < 0 || y >= N)
		{
			return 0;
		}
		return data[(x * N) + y];
	}
	auto operator[](const uint64_t x, const uint64_t y) -> float&
	{
#ifndef NDEBUG
		assert(x >= 0 && x < N);
		assert(y >= 0 && y < N);
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
		if (x < 0 || x >= 1)
		{
			return 0;
		}
		if (y < 0 || y >= 3)
		{
			return 0;
		}
		return data[(x * 1) + y];
	}
	auto operator[](const uint64_t x, const uint64_t y) -> float&
	{
#ifndef NDEBUG
		assert(x >= 0 && x < 1);
		assert(y >= 0 && y < 3);
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

using Matrix4 = Matrix<4>;
using Mat4 = Matrix<4>;
