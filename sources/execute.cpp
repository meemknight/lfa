#include "lfa\execute.h"

void execute(std::vector<std::string> &sigma, 
	std::vector<States> &states, 
	int beginStateIndex, 
	std::vector<Transitions> &transitions)
{
	std::cout << "enter word:\n";
	std::string w;
	std::cin >> w;
	std::cout << "\n";

	std::string currentState = states[beginStateIndex].name;

	for(auto i: w)
	{
		std::string nextTranzition = "";

		auto id = std::find_if(
			transitions.begin(),
			transitions.end(),
			[i, &currentState](const Transitions &t)
				{
					if (t.stateA == currentState
						&& t.symbol[0] == i
						)
					{
						return 1;
					}
					return 0;
				}
		);

		if(id == transitions.end())
		{

			std::cout << "Invalid Transition\nWord not accepted\n";
			return;

		}else
		{
			std::cout << "from " << currentState << "  to "
				<< (*id).stateB << "   with: " << (*id).symbol << "\n";
			currentState = (*id).stateB;
		}

	}

	auto id = std::find_if(states.begin(), states.end(),
		[&currentState](const States &s)
		{
			if(s.name == currentState)
			{
				return 1;
			}
			return 0;
		}
	);

	if(id == states.end())
	{
		errorOut("invalid state");
	}else
	{
		std::cout << "end state : " << (*id).name << "\n";

		if((*id).isEnd)
		{
			std::cout << "Word accepted";
		}else
		{
			std::cout << "Word not accepted";
		}
	}

	std::cout << "\n";

}
