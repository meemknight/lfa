#pragma once
#include "other.h"
#include <vector>
#include <string>

//returns if errors occured or not
bool execute(
	std::vector<std::string> &sigma,
	std::vector<States> &states,
	int beginStateIndex,
	std::vector<Transitions> &transitions,
	const std::string &word,
	bool &rezult,
	std::string &errMessage,
	std::string &traseu
);