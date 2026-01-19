#pragma once

#include "bgfx/bgfx.h"
#include <string>

class Shader
{
	public:
	private:
};

auto LoadShader(const std::string& filePath) -> bgfx::ShaderHandle;
auto CreateShaderProgram(const std::string& vertShader,
						 const std::string& fragShader) -> bgfx::ProgramHandle;
