#pragma once

#include <glfw3.h>
#define GLFW_EXPOSE_NATIVE_WAYLAND
#define GLFW_EXPOSE_NATIVE_X11
#include <glfw3native.h>
#include <string>

class EngineWindow
{
	public:
	EngineWindow();
	EngineWindow(const std::string& title, const int width, const int height);
	EngineWindow(const EngineWindow&) = delete;
	EngineWindow(EngineWindow&&) = delete;
	~EngineWindow();

	void Close();
	auto ShouldClose() const -> bool;

	void BeginContext() const;

	auto GetNativeHandle() const
	{
		return glfwGetWaylandWindow(this->handle);
		// return std::bit_cast<void*>(glfwGetX11Window(this->handle));
	}
	auto GetWidth() const -> int;
	auto GetHeight() const -> int;

	auto operator=(const EngineWindow&) -> EngineWindow& = delete;
	auto operator=(EngineWindow&& other) noexcept -> EngineWindow&;

	private:
	GLFWwindow* handle{nullptr};
	int width{0};
	int height{0};
};
