#include "mesh.h"
#include "shader.h"

#include <bgfx/bgfx.h>

Mesh::Mesh(const std::array<Vertex, 3>& data)
{
	static bgfx::VertexLayout layout;
	{
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	}
	this->vertexBuffer = bgfx::createVertexBuffer(
		bgfx::makeRef(data.data(), sizeof(data)), layout);
	this->indexBuffer = bgfx::createIndexBuffer(
		bgfx::makeRef(testIndices.data(), sizeof(testIndices)));
	this->shader = CreateShaderProgram(SHADERS "cubes.vert.bin",
									   SHADERS "cubes.frag.bin");
}
Mesh::Mesh(Mesh&& other) noexcept :
	vertexBuffer(other.vertexBuffer),
	indexBuffer(other.indexBuffer),
	shader(other.shader)
{
	other.shader = BGFX_INVALID_HANDLE;
	other.vertexBuffer = BGFX_INVALID_HANDLE;
	other.indexBuffer = BGFX_INVALID_HANDLE;
};
Mesh::~Mesh() { this->Destroy(); }

void Mesh::Draw() const
{
	bgfx::setVertexBuffer(0, this->vertexBuffer);
	bgfx::setIndexBuffer(this->indexBuffer);
	bgfx::submit(0, this->shader);
}

auto Mesh::operator=(Mesh&& other) noexcept -> Mesh&
{
	this->Destroy();

	this->shader = other.shader;
	this->vertexBuffer = other.vertexBuffer;
	this->indexBuffer = other.indexBuffer;

	other.shader = BGFX_INVALID_HANDLE;
	other.vertexBuffer = BGFX_INVALID_HANDLE;
	other.indexBuffer = BGFX_INVALID_HANDLE;

	return *this;
}

void Mesh::Destroy()
{
	if (bgfx::isValid(this->shader))
		bgfx::destroy(this->shader);
	if (bgfx::isValid(this->vertexBuffer))
		bgfx::destroy(this->vertexBuffer);
	if (bgfx::isValid(this->indexBuffer))
		bgfx::destroy(this->indexBuffer);
}
