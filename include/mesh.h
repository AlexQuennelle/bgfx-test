#pragma once

#include "color.h"
#include "matrix.h"
#include "vectorN.h"

#include <array>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <bgfx/bgfx.h>
#include <string>
#include <vector>

struct Vertex
{
	Vector3 pos{};
	Normal3 nor{Normal3::Up()};
	Color col{};
	Vector2 UV{};

	static void Init()
	{
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			// .add(bgfx::Attrib::Color1, 4, bgfx::AttribType::Uint8, true)
			// .add(bgfx::Attrib::Color2, 4, bgfx::AttribType::Uint8, true)
			// .add(bgfx::Attrib::Color3, 4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			// .add(bgfx::Attrib::TexCoord1, 2, bgfx::AttribType::Float)
			// .add(bgfx::Attrib::TexCoord2, 2, bgfx::AttribType::Float)
			// .add(bgfx::Attrib::TexCoord3, 2, bgfx::AttribType::Float)
			.end();
	}
	static bgfx::VertexLayout layout;
};

class Mesh
{
	public:
	Mesh() = default;
	Mesh(const aiMesh* aiMesh, const aiScene* scene);
	Mesh(const Mesh&) = delete;
	Mesh(Mesh&& other) noexcept;
	~Mesh();

	void Draw(bgfx::ProgramHandle& shader) const;

	auto operator=(const Mesh&) -> Mesh& = delete;
	auto operator=(Mesh&& other) noexcept -> Mesh&;

	friend auto LoadModel(const std::string& filepath)
		-> std::vector<std::pair<Mesh, Matrix<4>>>;

	struct Triangle
	{
		std::array<uint16_t, 3> indices{};
	};

	private:
	void Destroy();

	std::vector<Vertex> vertices;
	std::vector<Triangle> tris;
	bgfx::VertexBufferHandle vertexBuffer = BGFX_INVALID_HANDLE;
	bgfx::IndexBufferHandle indexBuffer = BGFX_INVALID_HANDLE;
};

auto LoadModel(const std::string& filepath)
	-> std::vector<std::pair<Mesh, Matrix<4>>>;
