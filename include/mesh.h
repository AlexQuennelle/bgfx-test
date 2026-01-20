#pragma once

#include "color.h"
#include "vector3.h"

#include <array>
#include <bgfx/bgfx.h>

struct Vertex
{
	float x;
	float y;
	float z;
	uint32_t col; // AGBR
	// Vector3 pos{};
	// Color col{};
	static void Init()
	{
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	}
	static bgfx::VertexLayout layout;
};

class Mesh
{
	public:
	Mesh() = default;
	Mesh(const std::array<Vertex, 3>& data);
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&& other) noexcept;
	~Mesh();

	void Draw() const;

	auto operator=(const Mesh&) -> Mesh& = delete;
	auto operator=(Mesh&& other) noexcept -> Mesh&;

	private:
	void Destroy();

	bgfx::VertexBufferHandle vertexBuffer = BGFX_INVALID_HANDLE;
	bgfx::IndexBufferHandle indexBuffer = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle shader = BGFX_INVALID_HANDLE;

	public:
};

static const std::array<Vertex, 3> testTri = {{
	// {.pos = {.x = -0.5f, .y = -0.5f, .z = 0.0f},
	//  .col = {255, 0, 0, 255}},

	// {.pos = {.x = 0.0f, .y = 0.5f, .z = 0.0f},
	//  .col = {0, 255, 0, 255}},

	// {.pos = {.x = 0.5f, .y = -0.5f, .z = 0.0f},
	//  .col = {0, 0, 255, 255}},
}};
static const std::array<int, 3> testIndices({0, 1, 2});
