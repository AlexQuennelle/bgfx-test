#pragma once

#include "color.h"
#include "vector3.h"

#include <array>
#include <bgfx/bgfx.h>

struct Vertex
{
	Vector3 pos{};
	Color col{};
};

class Mesh
{
	public:
	Mesh() = delete;
	Mesh(const std::array<Vertex, 3>& data);
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&&) = delete;
	~Mesh();

	auto operator=(const Mesh&) -> Mesh& = default;
	auto operator=(Mesh&&) -> Mesh& = default;

	private:
	bgfx::VertexBufferHandle vertexBuffer{0};
	bgfx::IndexBufferHandle indexBuffer{0};
	bgfx::ProgramHandle shader{0};

	public:
};

static const std::array<Vertex, 3> testTri = {{
	{.pos = {.x = -0.5f, .y = -0.5f, .z = 0.0f},
	 .col = {.r = 255, .g = 0, .b = 0, .a = 255}},

	{.pos = {.x = 0.0f, .y = 0.5f, .z = 0.0f},
	 .col = {.r = 0, .g = 255, .b = 0, .a = 255}},

	{.pos = {.x = 0.5f, .y = -0.5f, .z = 0.0f},
	 .col = {.r = 0, .g = 0, .b = 255, .a = 255}},
}};
static const std::array<int, 3> testIndices({0, 1, 2});
