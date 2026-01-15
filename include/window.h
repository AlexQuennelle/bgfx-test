#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#ifdef __linux__
#define GLFW_EXPOSE_NATIVE_WAYLAND
#define GLFW_EXPOSE_NATIVE_X11
#elifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#elifdef __EMSCRIPTEN__
// Web
#endif // __linux__
#ifndef __EMSCRIPTEN__
#include <GLFW/glfw3native.h>
#endif
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
#elifdef __EMSCRIPTEN__
		return canvasID.c_str();
#else
		return nullptr;
#endif
		// return std::bit_cast<void*>(glfwGetX11Window(this->handle));
	}
	auto GetWidth() const -> int;
	auto GetHeight() const -> int;

	auto operator=(const EngineWindow&) -> EngineWindow& = delete;
	auto operator=(EngineWindow&& other) noexcept -> EngineWindow&;

	static void ResizeCallback(GLFWwindow* handle, int x, int y);

	private:
	GLFWwindow* handle{nullptr};
	int width{0};
	int height{0};
	static std::vector<EngineWindow*> allWindows;
#ifdef __EMSCRIPTEN__
	const std::string canvasID{"canvas"};
#endif // __EMSCRIPTEN__
};
