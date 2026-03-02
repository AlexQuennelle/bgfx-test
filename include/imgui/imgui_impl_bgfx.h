/*
 * Copyright 2011-2026 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#pragma once

#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <imgui.h>

#define IMGUI_MBUT_LEFT 0x01
#define IMGUI_MBUT_RIGHT 0x02
#define IMGUI_MBUT_MIDDLE 0x04

// NOLINTBEGIN
inline auto imguiRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
	-> uint32_t
{ // NOLINTEND
	return 0
		   | (uint32_t(r) << 0)
		   | (uint32_t(g) << 8)
		   | (uint32_t(b) << 16)
		   | (uint32_t(a) << 24);
}

namespace bx
{
struct AllocatorI;
}

void ImGui_ImplBGFX_Init();
void ImGui_ImplBGFX_Shutdown();

void ImGui_ImplBGFX_NewFrame();
void ImGui_ImplBGFX_EndFrame();

namespace entry
{
class AppI;
}
void showExampleDialog(entry::AppI* _app, const char* _errorText = NULL);

namespace ImGui
{
#define IMGUI_FLAGS_NONE UINT8_C(0x00)
#define IMGUI_FLAGS_ALPHA_BLEND UINT8_C(0x01)

struct TextureBgfx
{
	bgfx::TextureHandle handle;
	uint8_t flags;
	uint8_t mip;
	uint32_t unused;
};

///
inline ImTextureID toId(bgfx::TextureHandle _handle, uint8_t _flags,
						uint8_t _mip)
{
	TextureBgfx tex{
		.handle = _handle,
		.flags = _flags,
		.mip = _mip,
		.unused = 0,
	};

	return bx::bitCast<ImTextureID>(tex);
}

// Helper function for passing bgfx::TextureHandle to ImGui::Image.
inline void Image(bgfx::TextureHandle _handle, uint8_t _flags, uint8_t _mip,
				  const ImVec2& _size, const ImVec2& _uv0 = ImVec2(0.0f, 0.0f),
				  const ImVec2& _uv1 = ImVec2(1.0f, 1.0f),
				  const ImVec4& _tintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
				  const ImVec4& _borderCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f))
{
	ImageWithBg(toId(_handle, _flags, _mip), _size, _uv0, _uv1, _borderCol,
				_tintCol);
}

// Helper function for passing bgfx::TextureHandle to ImGui::Image.
inline void Image(bgfx::TextureHandle _handle, const ImVec2& _size,
				  const ImVec2& _uv0 = ImVec2(0.0f, 0.0f),
				  const ImVec2& _uv1 = ImVec2(1.0f, 1.0f),
				  const ImVec4& _tintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
				  const ImVec4& _borderCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f))
{
	Image(_handle, IMGUI_FLAGS_ALPHA_BLEND, 0, _size, _uv0, _uv1, _tintCol,
		  _borderCol);
}

// Helper function for passing bgfx::TextureHandle to ImGui::ImageButton.
inline bool ImageButton(bgfx::TextureHandle _handle, uint8_t _flags,
						uint8_t _mip, const ImVec2& _size,
						const ImVec2& _uv0 = ImVec2(0.0f, 0.0f),
						const ImVec2& _uv1 = ImVec2(1.0f, 1.0f),
						const ImVec4& _bgCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f),
						const ImVec4& _tintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	return ImageButton("image", toId(_handle, _flags, _mip), _size, _uv0, _uv1,
					   _bgCol, _tintCol);
}

// Helper function for passing bgfx::TextureHandle to ImGui::ImageButton.
inline bool ImageButton(bgfx::TextureHandle _handle, const ImVec2& _size,
						const ImVec2& _uv0 = ImVec2(0.0f, 0.0f),
						const ImVec2& _uv1 = ImVec2(1.0f, 1.0f),
						const ImVec4& _bgCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f),
						const ImVec4& _tintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	return ImageButton(_handle, IMGUI_FLAGS_ALPHA_BLEND, 0, _size, _uv0, _uv1,
					   _bgCol, _tintCol);
}

///
inline void NextLine()
{
	SetCursorPosY(GetCursorPosY() + GetTextLineHeightWithSpacing());
}

///
inline bool MouseOverArea()
{
	return false
		   || ImGui::IsAnyItemActive()
		   || ImGui::IsAnyItemHovered()
		   || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)
		//			|| ImGuizmo::IsOver()
		;
}

} // namespace ImGui
