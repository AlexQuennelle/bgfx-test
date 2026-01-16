#include "mesh.h"

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
}
Mesh::~Mesh()
{
	bgfx::destroy(this->vertexBuffer);
}
