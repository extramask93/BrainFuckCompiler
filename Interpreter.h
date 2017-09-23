#pragma once
#include <string>
#include <array>
#include <stack>
#include <map>
#include <unordered_map>
#include <functional>

namespace defines
{
	const int mem_size{256};
	const std::array<char,9> availableChars{'<','>','+','-','.',',','[',']'};
}

class Interpreter
{
public:
	Interpreter();
	void RunScript(std::string const &name);
	~Interpreter();
private:
	std::array<char,defines::mem_size>::iterator p;
	int instPtr=0;
	std::vector<char> progMemory_;
	std::array<char,defines::mem_size> memory_;
	std::stack<char> stack_;
	std::map<int,int> bracketMap_;
	std::unordered_map<char,std::function<void()>> functions_;
	void ProcompileLoops();
	void LoadFromFile(std::string const &fname);
	void InitMemory();
};

