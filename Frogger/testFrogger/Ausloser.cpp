#include "Ausloser.h"

// Checken ob ein kommando da ist und dann herausgeben
void CommandQueue::push(const Kommando& command) {
	warteschleife.push(command);
}

Kommando	CommandQueue::pop() {
	Kommando c = warteschleife.front();
	warteschleife.pop();
	return c;
}
// Checken ob ein kommando leer ist
bool CommandQueue::isEmpty() const {
	return warteschleife.empty();
}