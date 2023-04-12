#include "Ausloser.h"


void CommandQueue::push(const Kommando& command) {
	warteschleife.push(command);
}

Kommando	CommandQueue::pop() {
	Kommando c = warteschleife.front();
	warteschleife.pop();
	return c;
}

bool CommandQueue::isEmpty() const {
	return warteschleife.empty();
}