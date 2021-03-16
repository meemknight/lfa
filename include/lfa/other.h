#pragma once
#include <string>
#include <algorithm>
#include <utility>
#include <iterator>

std::string toLower(const std::string &s)
{
	std::string newS = "";

	std::transform(s.begin(), s.end(), std::back_inserter(newS),
	[](unsigned char c) { return std::tolower(c); });

	return std::move(newS);
}


std::string removeEverythingAfterSpace(const std::string &s)
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


std::string removeEverythingAfterComa(const std::string &s)
{
	auto copy = s;
	auto f = copy.find(',');
	if (f != std::string::npos)
		copy.erase(copy.begin() + f, copy.end());

	return std::move(copy);
}

void errorOut(std::string msg)
{
	std::cout << msg;
	std::cin.clear();
	std::cin.get();
	exit(1);

}

std::vector<std::string> splitStringAtComas(const std::string &s)
{
	std::vector<std::string> ret;

	std::string curent = "";
	bool readingWord = 1;
	
	for(auto i: s)
	{
		if(i == ' ' && i == '\t')
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


bool hasInvalidCharacters(const std::string &s)
{
	auto f = s.find(',');
	if (f != std::string::npos)
		return 1;

	return 0;
}

