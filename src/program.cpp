#include "program.h"
#include "mesh.h"

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
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
Program::~Program() { glfwTerminate(); }

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
	init.resolution.reset = BGFX_RESET_VSYNC;
	init.resolution.width = static_cast<uint32_t>(this->win.GetHeight());
	init.resolution.height = static_cast<uint32_t>(this->win.GetWidth());

	init.platformData.nwh = this->win.GetNativeHandle();
	init.platformData.context = nullptr;
#ifdef __linux__
	init.platformData.ndt = glfwGetWaylandDisplay();
	init.platformData.type = bgfx::NativeWindowHandleType::Wayland;
#else
	init.platformData.type = bgfx::NativeWindowHandleType::Default;
#endif // __linux__
	bgfx::init(init);
	Vertex::Init();
	test = Mesh(testTri);
}
void Program::Update() { }
void Program::Draw() const
{
	this->win.BeginContext();
	glfwPollEvents();
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x00FF00FF, 1.0f,
					   0);
	bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(this->win.GetWidth()),
					  static_cast<uint16_t>(this->win.GetHeight()));
	// bgfx::touch(0);
	test.Draw();
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
