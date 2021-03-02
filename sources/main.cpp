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

#ifdef PLATFORM_WIN32
#include <Windows.h>
#endif

#undef min
#undef max

enum States
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
	std::vector<std::string> states;
	std::vector<std::string> finalStates;
	std::string beginState;
	std::vector<Transitions> transitions;


	std::ifstream f(RESOURCES_PATH "test.txt");
	permaAssertComment(f.is_open(), "file not found");
	
	int currentState = States::none;

	std::string line;
	while(std::getline(f, line))
	{
		auto commentBegin = line.find('#');
		if(commentBegin != std::string::npos)
		{
			line.erase(line.begin() + commentBegin, line.end());
		}
		
		if(line.empty())
		{
			continue;
		}

		std::istringstream linestream(line);
		std::string s;
		linestream >> s;
		
		auto f = s.find(',');
		if(f != std::string::npos)
		s.erase(s.begin() + f);

		if(s == "Sigma:")
		{
			currentState = States::sigma;
			continue;
		}else
		if(s == "States:")
		{
			currentState = States::states;
			continue;
		}else
		if(s == "Transitions:")
		{
			currentState = States::transitions;
			continue;
		}else
		if(s == "End")
		{
			currentState = States::none;
		}

		if(currentState == States::sigma)
		{
			
			sigma.push_back(s);
			continue;
		}

		if(currentState == States::states)
		{
			std::string s2;

			linestream >> s2;

			if(s2 == "S")
			{
				beginState = s;
			}else if(s2 == "F")
			{
				finalStates.push_back(s);
			}else
			{
				states.push_back(s);
			}

			continue;
		}

		if(currentState == States::transitions)
		{
			std::string s2, s3;
			linestream >> s2 >> s3;

			auto f = s2.find(',');
			if (f != std::string::npos)
				s2.erase(s2.begin() + f);

			transitions.emplace_back(s, s2, s3);
		}

	}

	
	for(auto &i : sigma)
	{
		std::cout << i << " ";
	}
	std::cout << "\n";
	for (auto &i : states)
	{
		std::cout << i << " ";
	}
	std::cout << "\n";

	for (auto &i : finalStates)
	{
		std::cout << i << " ";
	}
	std::cout << "\n";
	std::cout << beginState;
	std::cout << "\n";
	std::cout << "\n";

	for (auto &i : transitions)
	{
		std::cout << i << " " << "\n";
	}


	std::cin.clear();
	std::cin.get();
}