#include "program.h"

#include <bgfx/bgfx.h>
#include <glfw3.h>
#include <glfw3native.h>
#include <print>

Program::Program()
{
	if (glfwPlatformSupported(GLFW_PLATFORM_WAYLAND) != 0)
	{
		glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
	}
	// glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
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
	init.type = bgfx::RendererType::Vulkan;
	init.resolution.reset = BGFX_RESET_VSYNC;
	init.resolution.width
		= static_cast<uint32_t>(this->win.GetHeight());
	init.resolution.height
		= static_cast<uint32_t>(this->win.GetWidth());

	init.platformData.nwh = this->win.GetNativeHandle();
	init.platformData.context = nullptr;
	init.platformData.ndt = glfwGetWaylandDisplay();
	init.platformData.type
		= bgfx::NativeWindowHandleType::Wayland;

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
	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x334455FF, 1.0f,
					   0);
	bgfx::frame();
}
