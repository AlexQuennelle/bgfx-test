#include "mesh.h"
#include "shader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <bgfx/bgfx.h>
#include <iostream>
#include <print>
#include <ranges>
#include <vector>

bgfx::VertexLayout Vertex::layout;

Mesh::Mesh(const std::array<Vertex, 4>& data,
		   const std::array<uint16_t, 6>& indices)
{
	this->vertexBuffer = bgfx::createVertexBuffer(
		bgfx::makeRef(data.data(), sizeof(data)), Vertex::layout);
	this->indexBuffer = bgfx::createIndexBuffer(
		bgfx::makeRef(indices.data(), sizeof(indices)));
	this->shader = CreateShaderProgram(SHADERS "cubes.vert.bin",
									   SHADERS "cubes.frag.bin");
}
Mesh::Mesh(const std::array<Vertex, 8>& data,
		   const std::array<uint16_t, 36>& indices)
{
	this->vertexBuffer = bgfx::createVertexBuffer(
		bgfx::makeRef(data.data(), sizeof(data)), Vertex::layout);
	this->indexBuffer = bgfx::createIndexBuffer(
		bgfx::makeRef(indices.data(), sizeof(indices)));
	this->shader = CreateShaderProgram(SHADERS "cubes.vert.bin",
									   SHADERS "cubes.frag.bin");
}
Mesh::Mesh(const std::string& filepath)
{
	Assimp::Importer importer;
	const aiScene* scene
		= importer.ReadFile(filepath, 0x0
										  | aiProcess_JoinIdenticalVertices
										  | aiProcess_Triangulate
										  | aiProcess_SortByPType
										  | aiProcess_FixInfacingNormals
										  // | aiProcess_FlipWindingOrder
										  | aiProcess_OptimizeMeshes
										  | aiProcess_OptimizeGraph);
	// TODO: Add support for multi-mesh objects
	auto* mesh = scene->mMeshes[0]; // NOLINT

	// TODO: Add check to ensure colours are present
	namespace rv = std::ranges::views;
	std::vector<Vertex> vertexData;
	auto test = rv::zip(std::span(mesh->mVertices, mesh->mNumVertices),
						std::span(mesh->mColors[0], mesh->mNumVertices));
	vertexData.reserve(mesh->mNumVertices);
	for (auto [position, color] : test)
	{
		vertexData.push_back({
			{.x = position.x, .y = position.y, .z = position.z},
			{
				.r = static_cast<uint8_t>(std::round(color.r * 255)),
				.g = static_cast<uint8_t>(std::round(color.g * 255)),
				.b = static_cast<uint8_t>(std::round(color.b * 255)),
				.a = static_cast<uint8_t>(std::round(color.a * 255)),
			},
		});
	}

	std::vector<uint16_t> indices;
	for (uint32_t i{0}; i < mesh->mNumFaces; i++)
	{
		auto face{mesh->mFaces[i]};
		for (int j{0}; j < face.mNumIndices; j++)
		{
			indices.push_back(static_cast<uint16_t>(face.mIndices[j]));
		}
	}

	this->vertexBuffer = bgfx::createVertexBuffer(
		bgfx::copy(vertexData.data(),
				   static_cast<uint32_t>(vertexData.size() * sizeof(Vertex))),
		Vertex::layout);
	this->indexBuffer = bgfx::createIndexBuffer(
		bgfx::copy(indices.data(),
				   static_cast<uint32_t>(indices.size() * sizeof(uint16_t))));
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
