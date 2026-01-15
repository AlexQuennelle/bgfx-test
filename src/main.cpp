#include "program.h"

#include <print>
#ifdef __EMSCRIPTEN__
#include<emscripten/emscripten.h>
#endif // __EMSCRIPTEN__

auto main() -> int
{
	std::println("Hello, World!");
	Program game;
	game.Run();
}
