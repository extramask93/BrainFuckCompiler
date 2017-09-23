// BrainFuckInterpreter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Interpreter.h"
#include <iostream>
int main(int argc, char *argv[])
{
	if(argc != 2){
		std::cout<<"Usage: \nbint <filename>";
		return 1;
	}
	try
	{
		Interpreter interpreter;
		interpreter.RunScript(argv[1]);
	}
	catch(std::exception const &ex)
	{
		std::cerr<<ex.what();
		return 2;
	}
    return 0;
}

