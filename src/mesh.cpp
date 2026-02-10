#include "mesh.h"
#include "shader.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <bgfx/bgfx.h>
#include <iostream>
#include <print>
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
										  | aiProcess_OptimizeMeshes
										  | aiProcess_OptimizeGraph);
	auto* mesh = scene->mMeshes[0]; // NOLINT

	std::vector<Vertex> vertexData(mesh->mNumVertices);
	// this->vertexData.resize(mesh->mNumVertices);
	std::println("{} has {} vertices and {} faces", mesh->mName.C_Str(),
				 mesh->mNumVertices, mesh->mNumFaces);
	for (int i{0}; i < mesh->mNumVertices; i++)
	{
		auto floatCol{mesh->mColors[0][i]};
		auto meshPos{mesh->mVertices[i]};
		Vector3 pos{.x = meshPos.x, .y = meshPos.y, .z = meshPos.z};
		std::print("{}: {:.6f} {:.6f} {:.6f}", i, pos.x, pos.y, pos.z);
		Color col{
			.r = static_cast<uint8_t>(std::round(floatCol.r * 255)),
			.g = static_cast<uint8_t>(std::round(floatCol.g * 255)),
			.b = static_cast<uint8_t>(std::round(floatCol.b * 255)),
			// .a = static_cast<uint8_t>(std::round(floatCol.a * 255)),
			.a = 255,
		};
		std::println("  {:02x} {:02x} {:02x} {:02x}", col.r, col.g, col.b,
					 col.a);
		vertexData[i] = {.pos = pos, .col = col};
	}
	std::vector<uint16_t> indices;
	// {
	// 	2, 1, 0, //
	// 	0, 2, 3,
	// 	4, 5, 6, //
	// 	4, 6, 7,
	// 	8, 9, 10, //
	// 	8, 10, 11,
	// 	12, 13, 14, //
	// 	12, 14, 15,
	// 	16, 17, 18, //
	// 	16, 18, 19,
	// 	20, 21, 22, //
	// 	20, 22, 23,
	// };
	for (int i{0}; i < mesh->mNumFaces; i++)
	{
		auto face{mesh->mFaces[i]};
		for (int j{0}; j < face.mNumIndices; j++)
		{
			std::print("{}/", face.mIndices[j]);
			indices.push_back(static_cast<uint16_t>(face.mIndices[j]));
		}
		std::cout << '\n';
	}
	std::println("Index count: {}", indices.size());

	this->vertexBuffer = bgfx::createVertexBuffer(
		bgfx::makeRef(
			vertexData.data(),
			static_cast<uint32_t>(vertexData.size() * sizeof(Vertex))),
		Vertex::layout);
	this->indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(
		indices.data(),
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
