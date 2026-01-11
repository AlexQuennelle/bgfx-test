#include "window.h"

EngineWindow::EngineWindow() = default;
EngineWindow::EngineWindow(const std::string& title, const int width,
						   const int height) :
	width(width), height(height)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	this->handle // NOLINT
		= glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (this->handle == nullptr)
	{
	}
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

auto EngineWindow::operator=(EngineWindow&& other) noexcept -> EngineWindow&
{
	this->Close();

	this->handle = other.handle;
	this->width = other.width;
	this->height = other.height;

	other.handle = nullptr;

	return *this;
}
