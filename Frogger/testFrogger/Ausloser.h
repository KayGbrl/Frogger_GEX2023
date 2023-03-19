#pragma once

#include "Bewegung.h"
#include <queue>

class CommandQueue
{
public:
	void				push(const Kommando& command);
	Kommando				pop();
	bool				isEmpty() const;

private:
	std::queue<Kommando> warteschleife;

};

