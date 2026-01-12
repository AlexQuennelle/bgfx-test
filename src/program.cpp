#include "program.h"

#include <bgfx/bgfx.h>
#include <cstdint>
#include <glfw3.h>
#include <glfw3native.h>
#include <print>

Program::Program()
{
	if (glfwPlatformSupported(GLFW_PLATFORM_WAYLAND) != 0)
	{
		glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
	}
	else if (glfwPlatformSupported(GLFW_PLATFORM_X11) != 0)
	{
		glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
	}
	glfwInit();
	bgfx::init();
	this->win = EngineWindow(NAME, 400, 400);
}
Program::~Program() { glfwTerminate(); }

void Program::Run()
{
	this->win.BeginContext();

	bgfx::Init init;
	init.vendorId = BGFX_PCI_ID_NONE;
#ifdef __emscripten__
	init.type = bgfx::RendererType::OpenGL;
#else
	init.type = bgfx::RendererType::Vulkan;
#endif // __emscripten__
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

	while (!this->win.ShouldClose())
	{
		this->Update();
		this->Draw();
	}
	this->win.Close();
}

void Program::Update()
{
	// std::println("Update");
}
void Program::Draw() const
{
	this->win.BeginContext();
	glfwPollEvents();
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x00ff00ff, 1.0f,
					   0);
	bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(this->win.GetWidth()),
					  static_cast<uint16_t>(this->win.GetHeight()));
	bgfx::touch(0);
	std::println("test");
	bgfx::frame();
}
