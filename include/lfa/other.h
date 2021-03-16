#pragma once
#include <string>
#include <algorithm>
#include <utility>
#include <iterator>
#include <iostream>
#include <vector>

struct Transitions
{
	Transitions() {};
	Transitions(std::string a, std::string s, std::string b):
		stateA(a), symbol(s), stateB(b)
	{
	};

	std::string stateA;
	std::string	symbol;
	std::string stateB;


	friend std::ostream &operator<<(std::ostream &output, const Transitions &t)
	{
		output << t.stateA << " " << t.symbol << " " << t.stateB;
		return output;
	}
};

struct States
{
	States() {};
	States(std::string name):name(name) {};
	States(std::string name, int isBegin, int isEnd)
		:name(name), isBegin(isBegin), isEnd(isEnd)
	{
	};

	std::string name = "";
	int isBegin = 0;
	int isEnd = 0;
};


inline std::string toLower(const std::string &s)
{
	std::string newS = "";

	std::transform(s.begin(), s.end(), std::back_inserter(newS),
	[](unsigned char c) { return std::tolower(c); });

	return std::move(newS);
}


inline std::string removeEverythingAfterSpace(const std::string &s)
{
	auto copy = s;
	auto f = copy.find(' ');
	if (f != std::string::npos)
		copy.erase(copy.begin() + f, copy.end());

	f = copy.find('\t');
	if (f != std::string::npos)
		copy.erase(copy.begin() + f, copy.end());

	return std::move(copy);
}

inline std::string removeLastSpaces(const std::string &s)
{
	auto copy = s;

	while(true)
	{
		if(
			!copy.empty() && 
				(	
				copy[copy.size() - 1] == ' ' ||
				copy[copy.size() - 1] == '\t'
				)
			)
		{
			copy.pop_back();
		}else
		{
			break;
		}
	}


	return std::move(copy);

}


inline std::string removeEverythingAfterComa(const std::string &s)
{
	auto copy = s;
	auto f = copy.find(',');
	if (f != std::string::npos)
		copy.erase(copy.begin() + f, copy.end());

	return std::move(copy);
}

inline void errorOut(std::string msg)
{
	std::cout << msg;
	std::cin.clear();
	std::cin.ignore();
	std::cin.get();
	exit(1);

}

inline std::vector<std::string> splitStringAtComas(const std::string &s2)
{
	std::vector<std::string> ret;

	std::string s = removeLastSpaces(s2);

	std::string curent = "";
	bool readingWord = 0;
	
	for(auto i: s)
	{
		if(i == ' ' || i == '\t')
		{
			if(readingWord)
			{
				errorOut("invalid space in word token :" + curent);
			}else
			{
				continue;
			}
		}else if(i == ',')
		{
			if(readingWord)
			{
				if (curent != "")
				{
					ret.push_back(curent);
				}else
				{
					errorOut("no word in between commas");
				}
				curent = "";
				readingWord = 0;
			}else
			{
				errorOut("no word in between commas");
			}

		}else
		{
			readingWord = 1;
			curent += i;
		}
	
	}

	if(curent != "")
	{
		ret.push_back(curent);
	}

	return ret;
}


inline bool hasInvalidCharacters(const std::string &s)
{
	auto f = s.find(',');
	if (f != std::string::npos)
		return 1;

	return 0;
}

