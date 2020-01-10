#pragma once
#include <vector>

class Delegate
{
public:
	/* Add new function */
	void AddFunction(void (*func)());

	/* Remove function */
	void RemoveFunction(void (*func)());

	/* Call all stored functions */
	void Execute();

protected:
	std::vector<void (*)()> functions;

};

