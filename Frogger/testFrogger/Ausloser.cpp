#include "Ausloser.h"


void CommandQueue::push(const Kommando& command) {
	queue.push(command);
}

Kommando	CommandQueue::pop() {
	Kommando c = queue.front();
	queue.pop();
	return c;
}

bool CommandQueue::isEmpty() const {
	return queue.empty();
}