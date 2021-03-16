#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <cctype>

#include "lfa/tools.h"
#include "lfa/other.h"

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

struct Transitions
{
	Transitions() {};
	Transitions(std::string a, std::string s, std::string b):
		stateA(a), symbol(s), stateB(b)
	{};

	std::string stateA;
	std::string	symbol;
	std::string stateB;


	friend std::ostream &operator<<(std::ostream &output, const Transitions &t)
	{
		output << t.stateA   << " " << t.symbol << " " << t.stateB;
		return output;
	}
};

struct States
{
	States() {};
	States(std::string name):name(name) {};
	States(std::string name, int isBegin, int isEnd)
		:name(name), isBegin(isBegin), isEnd(isEnd) {};

	std::string name = "";
	int isBegin = 0;
	int isEnd = 0;
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

	std::vector<std::string> sigma;
	
	std::vector<States> states;
	int beginStateIndex = -1;

	std::vector<Transitions> transitions;


	std::ifstream f(RESOURCES_PATH "test.txt");
	permaAssertComment(f.is_open(), "file not found");
	
	int currentState = ReadStates::none;

	std::string line;
	while(std::getline(f, line))
	{

	#pragma region erase comments
		auto commentBegin = line.find('#');
		if(commentBegin != std::string::npos)
		{
			line.erase(line.begin() + commentBegin, line.end());
		}
	#pragma endregion

	#pragma region ignore empty lines
		line = removeLastSpaces(line);

		if(line.empty())
		{
			continue;
		}
	#pragma endregion

	#pragma region get the first word on line (s)
		std::istringstream linestream(line);
		std::string s;
		linestream >> s;
		
		s = removeEverythingAfterComa(s);
		
		s = removeEverythingAfterSpace(s);

	#pragma endregion


		if(toLower(s) == "sigma:")
		{
			currentState = ReadStates::sigma;
			continue;
		}else
		if(toLower(s) == "states:")
		{
			currentState = ReadStates::states;
			continue;
		}else
		if(toLower(s) == "transitions:")
		{
			currentState = ReadStates::transitions;
			continue;
		}else
		if(toLower(s) == "end")
		{
			currentState = ReadStates::none;
		}

		if(currentState == ReadStates::sigma)
		{
			auto parseElements = splitStringAtComas(line);

			if (parseElements.size() == 1)
			{
				sigma.push_back(parseElements[0]);
				continue;
			}else
			{
				errorOut("sintax err reading sigma: " + line);
			}

		}

		if(currentState == ReadStates::states)
		{
			auto parseElements = splitStringAtComas(line);

			if(parseElements.size() > 2)
			{
				errorOut("too many arguments: " + line);
			}

			if(parseElements.size() == 0)
			{
				errorOut("no elements");
			}

			if (parseElements.size() == 1)
			{
				parseElements.push_back("");
			}

			std::string s = parseElements[0];
			std::string s2 = parseElements[1];

			if(toLower(s2) == "s")
			{
				states.push_back(States(s, 1, 0));
				if(beginStateIndex != -1)
				{
					std::cout << "err, 2 begin states or more\n";
					std::cin.clear();
					std::cin.get();
					return 0;
				}

				beginStateIndex = states.size() - 1;

			}else if(toLower(s2) == "f")
			{
				states.push_back(States(s, 0, 1));
			}else if(s2 == "")
			{
				states.push_back(s);
			}else
			{
				errorOut("err, invalid parse in state\n");
			}

			continue;
		}

		if(currentState == ReadStates::transitions)
		{
			auto parseElements = splitStringAtComas(line);

			if (parseElements.size() != 3)
			{
				errorOut("sintax error transitions: " + line);
			}

			std::string s, s2, s3;
			
			s = parseElements[0];
			s2 = parseElements[1];
			s3 = parseElements[2];

			transitions.emplace_back(s, s2, s3);
		}

	}

	std::cout << "sigma:\n";
	for(auto &i : sigma)
	{
		std::cout << i << " ";
	}
	
	std::cout << "\n\nStates:\n";
	for (auto &i : states)
	{
		std::cout << i.name <<" isBegin:" <<i.isBegin 
			<< " isEnd:"<<i.isEnd << "\n";
	}


	std::cout << "\n\nTransitions:\n";
	for (auto &i : transitions)
	{
		std::cout << i << " " << "\n";
	}


	std::cin.clear();
	std::cin.get();
}