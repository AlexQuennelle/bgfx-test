#include "shader.h"

#include <filesystem>
#include <fstream>
#include <print>
#include <string>

auto LoadShader(const std::string& filePath) -> bgfx::ShaderHandle
{
	bgfx::ShaderHandle handle = BGFX_INVALID_HANDLE;

	std::ifstream file{filePath};
	auto size{std::filesystem::file_size(filePath)};
	if (file.is_open())
	{
		std::string data{std::istreambuf_iterator<char>(file),
						 std::istreambuf_iterator<char>()};
		const bgfx::Memory* mem
			= bgfx::copy(data.data(), static_cast<uint32_t>(size));
		handle = bgfx::createShader(mem);
	}
	else
	{
		std::println("ERROR: Unable to open file {}", filePath);
	}

	return handle;
}

auto CreateShaderProgram(const std::string& vertShader,
						 const std::string& fragShader) -> bgfx::ProgramHandle
{
	auto vert{LoadShader(vertShader)};
	auto frag{LoadShader(fragShader)};
	return bgfx::createProgram(vert, frag, true);
}
