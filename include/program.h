#pragma once

#include "window.h"
// #define __EMSCRIPTEN__

class Program
{
	public:
	Program();
	Program(const Program&) = delete;
	Program(Program&&) = delete;
	~Program();

	void Run();

	auto operator=(const Program&) -> Program& = delete;
	auto operator=(Program&&) -> Program& = delete;

#ifdef __EMSCRIPTEN__
	friend void WebLoop(void* arg);
#endif // __EMSCRIPTEN__

	private:
	void Init();
	void Update();
	void Draw() const;

	EngineWindow win;
};

#ifdef __EMSCRIPTEN__
void WebLoop(void* arg);
#endif // __EMSCRIPTEN__
