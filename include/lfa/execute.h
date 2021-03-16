#pragma once
#include "other.h"
#include <vector>
#include <string>

void execute(
	std::vector<std::string> &sigma,
	std::vector<States> &states,
	int beginStateIndex,
	std::vector<Transitions> &transitions
);