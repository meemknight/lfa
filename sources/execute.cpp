#include "lfa\execute.h"

bool execute(
	std::vector<States> &states,
	int beginStateIndex,
	std::vector<Transitions> &transitions,
	const std::string &word,
	bool &rezult,
	std::string &errMessage,
	std::string &traseu
)
{
	errMessage.clear();
	rezult = 0;
	traseu = "Traseu:";

	std::string currentState = states[beginStateIndex].name;

	traseu += " ";
	traseu += currentState;

	for(auto i: word)
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
			errMessage = "Warning: Invalid Transition, word not accepted";
			rezult = 0;
			return 1;

		}else
		{
			//std::cout << "from " << currentState << "  to "
			//	<< (*id).stateB << "   with: " << (*id).symbol << "\n";
			currentState = (*id).stateB;

			traseu += " ";
			traseu += currentState;
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
		errMessage = "Invalid end state. The inputs are probably wrong.";
		return 0;
	}else
	{
		if((*id).isEnd)
		{
			rezult = 1;
			return 1;
		}else
		{
			rezult = 0;
			return 1;
		}
	}


}

