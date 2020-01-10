#include "Delegate.h"

void Delegate::AddFunction(void (*func)())
{
	functions.emplace_back(func);
}

void Delegate::RemoveFunction(void (*func)())
{
	auto iter = std::find(functions.begin(), functions.end(), func);
	functions.erase(iter);
}

void Delegate::Execute()
{
	for (auto& func : functions)
	{
		(*func)();
	}
}
