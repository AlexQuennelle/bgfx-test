#pragma once

#include <glfw3.h>
#ifdef __linux__
#define GLFW_EXPOSE_NATIVE_WAYLAND
#define GLFW_EXPOSE_NATIVE_X11
#elifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif // __linux__
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
#ifdef _WIN32
		return glfwGetWin32Window(this->handle);
#elifdef __linux__
		return glfwGetWaylandWindow(this->handle);
#else
		return nullptr;
#endif
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
