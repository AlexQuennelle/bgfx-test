#pragma once

#include "color.h"
#include "vector3.h"

#include <array>
#include <bgfx/bgfx.h>

struct Vertex
{
	// float x;
	// float y;
	// float z;
	Vector3 pos{};
	// uint32_t col; // AGBR
	Color col{};
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
	Mesh(const std::array<Vertex, 8>& data);
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

static const std::array<Vertex, 8> testCube = {{
	{.pos = {-1.0f, 1.0f, 1.0f},
	 .col = { 0x00, 0x00, 0x00, 0xff }},
	{.pos = {1.0f, 1.0f, 1.0f},
	 .col = { 0xff, 0x00, 0x00, 0xff }},
	{.pos = {-1.0f, -1.0f, 1.0f},
	 .col = { 0x00, 0xff, 0x00, 0xff }},
	{.pos = {1.0f, -1.0f, 1.0f},
	 .col = { 0xff, 0xff, 0x00, 0xff }},
	{.pos = {-1.0f, 1.0f, -1.0f},
	 .col = { 0x00, 0x00, 0xff, 0xff }},
	{.pos = {1.0f, 1.0f, -1.0f},
	 .col = { 0xff, 0x00, 0xff, 0xff }},
	{.pos = {-1.0f, -1.0f, -1.0f},
	 .col = { 0x00, 0xff, 0xff, 0xff }},
	{.pos = {1.0f, -1.0f, -1.0f},
	 .col = { 0xff, 0xff, 0xff, 0xff }},
}};
static const std::array<uint16_t, 36> testIndices({
	0, 1, 2, 1, 3, 2, // 0
	4, 6, 5, 5, 6, 7, // 2
	0, 2, 4, 4, 2, 6, // 4
	1, 5, 3, 5, 7, 3, // 6
	0, 4, 1, 4, 5, 1, // 8
	2, 3, 6, 6, 3, 7, // 10
});
