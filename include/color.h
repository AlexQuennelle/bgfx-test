#pragma once

#include <cstdint>

struct Color
{
	uint8_t a{255};
	uint8_t b{255};
	uint8_t g{255};
	uint8_t r{255};

	auto RGBA() -> uint32_t
	{
		return 0u
			   | (static_cast<uint32_t>(this->r) << 24)
			   | (static_cast<uint32_t>(this->g) << 16)
			   | (static_cast<uint32_t>(this->b) << 8)
			   | (static_cast<uint32_t>(this->a) << 0);
	}
	auto ABGR() -> uint32_t
	{
		return 0u
			   | (static_cast<uint32_t>(this->a) << 0)
			   | (static_cast<uint32_t>(this->b) << 8)
			   | (static_cast<uint32_t>(this->g) << 16)
			   | (static_cast<uint32_t>(this->r) << 24);
	}

	explicit operator uint32_t() { return this->RGBA(); }
};
