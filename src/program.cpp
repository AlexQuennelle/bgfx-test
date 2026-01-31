#include "program.h"
#include "mesh.h"
#include "shader.h"

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include <cstdint>
#ifndef __EMSCRIPTEN__
#include <GLFW/glfw3native.h>
#else
#include <emscripten/emscripten.h>
#endif // !__EMSCRIPTEN__

Program::Program()
{
#ifndef __EMSCRIPTEN__
	if (glfwPlatformSupported(GLFW_PLATFORM_WAYLAND) != 0)
	{
		glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
	}
	else if (glfwPlatformSupported(GLFW_PLATFORM_X11) != 0)
	{
		glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
	}
#endif // !__EMSCRIPTEN__
	glfwInit();
	bgfx::init();
	this->win = EngineWindow(NAME, 400, 400);
}
Program::~Program()
{
	bgfx::shutdown();
	glfwTerminate();
}

void Program::Run()
{
	this->Init();

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(WebLoop, this, 0, 1);
#else
	while (!this->win.ShouldClose())
	{
		this->Update();
		this->Draw();
	}
	this->win.Close();
#endif // !__EMSCRIPTEN__
}

void Program::Init()
{
	this->win.BeginContext();

	bgfx::Init init;
	init.vendorId = BGFX_PCI_ID_NONE;
#ifdef __EMSCRIPTEN__
	init.type = bgfx::RendererType::OpenGL;
#else
	if (Backend == "VULKAN")
		init.type = bgfx::RendererType::Vulkan;
	else if (Backend == "OPEN_GL")
		init.type = bgfx::RendererType::OpenGL;
	else
		init.type = bgfx::RendererType::Noop;
#endif // __EMSCRIPTEN__

	init.platformData.nwh = this->win.GetNativeHandle();
#ifdef __linux__
	init.platformData.ndt = glfwGetWaylandDisplay();
	init.platformData.type = bgfx::NativeWindowHandleType::Wayland;
#else
	init.platformData.type = bgfx::NativeWindowHandleType::Default;
#endif // __linux__
	init.platformData.context = nullptr;

	init.resolution.width = static_cast<uint32_t>(this->win.GetHeight());
	init.resolution.height = static_cast<uint32_t>(this->win.GetWidth());
	init.resolution.reset = BGFX_RESET_VSYNC;

	bgfx::init(init);

	// HACK: BGFX example code
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x00FF00FF, 1.0f,
					   0);

	Vertex::Init();
	// m_vbh = bgfx::createVertexBuffer(
	// 	bgfx::makeRef(testCube.data(), sizeof(testCube)), Vertex::layout);
	// m_ibh = bgfx::createIndexBuffer(
	// 	bgfx::makeRef(testIndices.data(), sizeof(testIndices)));

	// this->shader = CreateShaderProgram(SHADERS "cubes.vert.bin",
	// 								   SHADERS "cubes.frag.bin");

	test = Mesh(testCube);
}
void Program::Update() { }
void Program::Draw() const
{
	this->win.BeginContext();
	glfwPollEvents();
	const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
	const bx::Vec3 eye = {0.0f, 0.0f, -35.0f};
	{
		float view[16];
		bx::mtxLookAt(view, eye, at);

		float proj[16];
		bx::mtxProj(proj, 60.0f,
					static_cast<float>(this->win.GetWidth())
						/ static_cast<float>(this->win.GetWidth()),
					0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(0, view, proj);

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(this->win.GetWidth()),
						  static_cast<uint16_t>(this->win.GetHeight()));
	}

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xFFFFFFFF, 1.0f,
					   0);
	bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(this->win.GetWidth()),
					  static_cast<uint16_t>(this->win.GetHeight()));
	bgfx::touch(0);

	uint64_t state = 0
					 | BGFX_STATE_WRITE_R
					 | BGFX_STATE_WRITE_G
					 | BGFX_STATE_WRITE_B
					 | BGFX_STATE_WRITE_A
					 | BGFX_STATE_WRITE_Z
					 | BGFX_STATE_DEPTH_TEST_LESS
					 | BGFX_STATE_CULL_CW
					 | BGFX_STATE_MSAA;
	for (uint32_t yy = 0; yy < 11; ++yy)
	{
		for (uint32_t xx = 0; xx < 11; ++xx)
		{
			float mtx[16];
			bx::mtxRotateXY(mtx, xx * 0.21f, yy * 0.37f);
			mtx[12] = -15.0f + float(xx) * 3.0f;
			mtx[13] = -15.0f + float(yy) * 3.0f;
			mtx[14] = 0.0f;

			// Set model matrix for rendering.
			bgfx::setTransform(mtx);

			// Set vertex and index buffer.
			// bgfx::setVertexBuffer(0, m_vbh);
			// bgfx::setIndexBuffer(m_ibh);
			this->test.Draw();

			// Set render states.
			// bgfx::setState(state);

			// Submit primitive for rendering to view 0.
			// bgfx::submit(0, shader);
		}
	}
	// bgfx::touch(0);
	// test.Draw();
	bgfx::frame();
}

#ifdef __EMSCRIPTEN__
void WebLoop(void* arg)
{
	auto* program = static_cast<Program*>(arg);
	program->Update();
	program->Draw();
}
#endif // __EMSCRIPTEN__
