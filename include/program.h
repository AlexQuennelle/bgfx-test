#pragma once

#include "window.h"

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

	private:
	void Update();
	void Draw() const;

	EngineWindow win;
};
