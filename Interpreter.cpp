#include "Interpreter.h"
#include <fstream>
#include <iostream>


Interpreter::Interpreter()
{
	functions_['>'] = [this]()
	{
		++p;
		if(p>=memory_.end())
			throw std::runtime_error{"Accessing out of range memory"};
	};
	functions_['<'] = [this]()
	{
		--p;
		if(p<memory_.begin())
			throw std::runtime_error{"Accessing out of range memory"};
	};
	functions_['+'] = [this](){++(*p);};
	functions_['-'] = [this](){--(*p);};
	functions_['.'] = [this](){std::cout<<*p;};
	functions_[','] = [this](){std::cin>>*p;};
	functions_['['] = [this]()
	{
		if(*p==0)
			instPtr=bracketMap_[instPtr];

	};
	functions_[']'] = [this](){instPtr=bracketMap_[instPtr]-1;};
}

void Interpreter::RunScript(std::string const& name)
{
	InitMemory();
	LoadFromFile(name);
	ProcompileLoops();
	for(instPtr=0;instPtr<progMemory_.size();++instPtr)
	{
		auto t=functions_[progMemory_[instPtr]];
		t();
	}
}

void Interpreter::LoadFromFile(std::string const& fname)
{
	std::fstream file;
	file.open(fname,std::fstream::in);
	char buffer;
	while(file.get(buffer))
	{
		
		auto r=std::find(std::begin(defines::availableChars),std::end(defines::availableChars),buffer);
		if(r==std::end(defines::availableChars))
			continue;
		progMemory_.emplace_back(buffer);
	}
	file.close();
}

void Interpreter::InitMemory()
{
	memory_.fill(0);
	p=memory_.begin();
}

void Interpreter::ProcompileLoops()
{
	if(progMemory_.empty()){return;}
	for(int i=0;i<progMemory_.size();++i)
	{
		if(progMemory_[i]=='[')
			stack_.push(i);
		else if(progMemory_[i]==']')
		{
			if(stack_.empty())
				throw std::runtime_error{"Mismatched paretheses"};
			bracketMap_[i]=stack_.top();
			bracketMap_[stack_.top()]=i;
			stack_.pop();
		}
	}
}


Interpreter::~Interpreter()
{
}
