#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <cctype>

#include "lfa/tools.h"
#include "lfa/other.h"
#include "lfa/execute.h"

#ifdef PLATFORM_WIN32
#include <Windows.h>
#endif

#undef min
#undef max

enum ReadStates
{
	none = 0,
	sigma,
	states,
	transitions,
};

int main()
{

#ifdef PLATFORM_WIN32
#ifdef _MSC_VER 
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
	std::cout.sync_with_stdio();
#endif
#endif

	std::ifstream f(RESOURCES_PATH "proiect1.txt");
	if(!f.is_open())
	{
		std::cout << "err openning file\n";
		std::cin.get();
		return 0;
	}

	int statesCount, transitionsCount;
	f >> statesCount >> transitionsCount;

	std::vector<States> states;
	for(int i=0; i<statesCount; i++)
	{
		states.emplace_back(std::to_string(i));
	}

	std::vector<Transitions> transitions;
	for (int i = 0; i < transitionsCount; i++)
	{
		int state1, state2;
		std::string symbol;

		f >> state1 >> state2 >> symbol;

		transitions.emplace_back(std::to_string(state1), symbol, std::to_string(state2));

	}

	int beginState;
	f >> beginState;
	
	f.ignore();
	std::string line;
	std::getline(f, line);
	std::stringstream endStatesLine(line);
	
	int entStateElement;
	while(endStatesLine >> entStateElement)
	{
		states[entStateElement].isEnd = true;
	}

	int tests;
	f >> tests;

	std::string word;
	while(f >> word)
	{
		bool rezult = 0;
		std::string errMsg;
		std::string traseu;

		bool good = execute(states, beginState, transitions, word, rezult, errMsg, traseu);

		if (!good)
		{
			std::cout << "corupt input\n";
			std::cout << errMsg << "\n";
		}
		else
		{
			if (rezult)
			{
				std::cout << "DA\n";
				std::cout << traseu << "\n";

			}
			else
			{
				std::cout << "NU\n";
			}
		}
	}

	std::cin.get();
}