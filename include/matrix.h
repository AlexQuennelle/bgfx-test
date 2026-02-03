#pragma once

#include "vectorN.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <format>
#include <iostream>

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
	constexpr auto GetWidth() const -> uint64_t { return W; }
	constexpr auto GetHeight() const -> uint64_t { return H; }

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
		// auto transpose{other.Transpose()};
		Matrix mat{};
		for (uint64_t y{0}; y < H; y++)
		{
			for (uint64_t x{0}; x < W2; x++)
			{
				mat[x, y] = 0;
				for (int i{0}; i < W; i++)
				{
					mat[x, y] += *(this)[i, y] * other[x, i];
				}
			}
		}
		return mat;
	}

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
