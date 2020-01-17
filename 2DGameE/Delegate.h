#pragma once
#include <vector>

template<typename FunctionType = void (*)()>
class Delegate
{
public:
	void Delegate::AddFunction(FunctionType)
	{
		functions.emplace_back(func);
	}

	void Delegate::RemoveFunction(FunctionType)
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

protected:
	std::vector<FunctionType> functions;

};
