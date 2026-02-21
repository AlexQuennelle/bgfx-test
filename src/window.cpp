#include "window.h"

#include <bgfx/bgfx.h>

EngineWindow::EngineWindow() = default;
EngineWindow::EngineWindow(const std::string& title, const int width,
						   const int height) :
	width(width), height(height)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, 0);
	this->handle // NOLINT
		= glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (this->handle == nullptr)
	{
	}

	glfwSetWindowUserPointer(this->handle, this);

	glfwSetWindowSizeCallback(this->handle, ResizeCallback);
}
EngineWindow::~EngineWindow() { this->Close(); }

void EngineWindow::Close()
{
	glfwMakeContextCurrent(nullptr);
	glfwDestroyWindow(this->handle);
	this->handle = nullptr;
}
auto EngineWindow::ShouldClose() const -> bool
{
	return glfwWindowShouldClose(this->handle) != 0;
}

void EngineWindow::BeginContext() const
{
	glfwMakeContextCurrent(this->handle);
};

auto EngineWindow::GetWidth() const -> int { return this->width; };
auto EngineWindow::GetHeight() const -> int { return this->height; };
auto EngineWindow::GetGLFWHandle() const -> GLFWwindow* { return this->handle; }
auto EngineWindow::GetMousePos() const -> Point2D
{
	double x{};
	double y{};
	glfwGetCursorPos(this->handle, &x, &y);
	return {.x = static_cast<int32_t>(x), .y = static_cast<int32_t>(y)};
}

auto EngineWindow::operator=(EngineWindow&& other) noexcept -> EngineWindow&
{
	this->Close();

	this->handle = other.handle;
	this->width = other.width;
	this->height = other.height;

	glfwSetWindowUserPointer(this->handle, this);

	other.handle = nullptr;

	return *this;
}

void EngineWindow::ResizeCallback(GLFWwindow* handle, int x, int y)
{
	auto& wrapper
		= *static_cast<EngineWindow*>(glfwGetWindowUserPointer(handle));
	wrapper.width = x;
	wrapper.height = y;
	bgfx::reset(static_cast<uint32_t>(x), static_cast<uint32_t>(y),
				BGFX_RESET_VSYNC);
	bgfx::setViewRect(0, 0, 0, static_cast<uint16_t>(x),
					  static_cast<uint16_t>(y));
	bgfx::touch(0);
}
