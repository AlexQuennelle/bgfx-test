#pragma once

#include "mesh.h"
#include "window.h"

static constexpr std::string Backend = BACKEND;

static Vertex s_cubeVertices[] = {
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
};

static const uint16_t s_cubeTriList[] = {
	0, 1, 2, 1, 3, 2, // 0
	4, 6, 5, 5, 6, 7, // 2
	0, 2, 4, 4, 2, 6, // 4
	1, 5, 3, 5, 7, 3, // 6
	0, 4, 1, 4, 5, 1, // 8
	2, 3, 6, 6, 3, 7, // 10
};

class Program
{
	public:
	Program();
	Program(const Program&) = delete;
	Program(Program&&) = delete;
	~Program();

	void Run();

	auto operator=(const Program&) -> Program& = delete;
	auto operator=(Program&&) -> Program& = delete;

#ifdef __EMSCRIPTEN__
	friend void WebLoop(void* arg);
#endif // __EMSCRIPTEN__

	private:
	void Init();
	void Update();
	void Draw() const;

	EngineWindow win;
	Mesh test;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle shader = BGFX_INVALID_HANDLE;
};

#ifdef __EMSCRIPTEN__
void WebLoop(void* arg);
#endif // __EMSCRIPTEN__
