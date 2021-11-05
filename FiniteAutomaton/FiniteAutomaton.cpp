#include "FiniteAutomaton.hpp"
#include <fstream>
#include  <tuple>
#include <iostream>
#include <map>
#include <tuple>

FiniteAutomaton::FiniteAutomaton(std::string fileName)
	: states{std::vector<std::string>()}, 
	initialState { std::string() },
	finalStates {std::vector<std::string>()},
	transitions {std::vector<Transition>()},
	alphabet { std::vector<std::string>()}
{
	this->deterministic = true;
	this->readFile(fileName);
}

std::vector<std::string> FiniteAutomaton::getStates()
{
	return this->states;
}

std::string FiniteAutomaton::getInitialState()
{
	return this->initialState;
}

std::vector<std::string> FiniteAutomaton::getFinalStates()
{
	return this->finalStates;
}

std::vector<Transition> FiniteAutomaton::getTransitions()
{
	return this->transitions;
}

std::vector<std::string> FiniteAutomaton::getAlphabet()
{
	return this->alphabet;
}

bool FiniteAutomaton::isDeterministic()
{
	for (auto state : this->states)
	{
		std::map<std::tuple<std::string, std::string>, int> t;
		for (auto transition : this->transitions)
		{
			if (transition.getState1() == state)
			{
				std::tuple<std::string, std::string> tuple(transition.getState1(), transition.getAlphabetElem());
				if (t.find(tuple) != t.end())
				{
					this->deterministic = true;
					return false;
				}
				else
				{
					t.insert(std::pair<std::tuple<std::string, std::string>, int>(tuple, 0));
				}
			}
		}
	}

	return true;
}

bool FiniteAutomaton::acceptsSequence(std::string sequence)
{
	return false;
}

void FiniteAutomaton::printStates()
{
	for (auto s : this->states)
	{
		std::cout << s << " ";
	}
}

void FiniteAutomaton::printAlphabet()
{
	for (auto s : this->alphabet)
	{
		std::cout << s << " ";
	}
}

void FiniteAutomaton::printTransitions()
{
	for (Transition t : this->transitions)
	{
		std::cout << t.getState1() << " " << t.getAlphabetElem() << " " << t.getState2() << "\n";
	}
}

void FiniteAutomaton::printFinalStates()
{
	for (auto s : this->finalStates)
	{
		std::cout << s << " ";
	}
}

void FiniteAutomaton::readFile(std::string fileName)
{
	std::fstream file(fileName, std::ios::in);
	if (file.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			std::string categoryLen;
			getline(file, categoryLen);
			std::string line;

			for (int j = 0; j < atoi(categoryLen.c_str()); ++j)
			{
				getline(file, line);
				if (i == 0)
				{
					//initial state
					this->initialState = line;
					if (std::find(this->alphabet.begin(), this->alphabet.end(), line) == this->alphabet.end())
					{
						this->alphabet.push_back(line);
					}
					if (std::find(this->states.begin(), this->states.end(), line) == this->states.end())
					{
						this->states.push_back(line);
					}
				}
				else if (i == 1)
				{
					// final states
					if (std::find(this->alphabet.begin(), this->alphabet.end(), line) == this->alphabet.end())
					{
						this->alphabet.push_back(line);
					}
					if (std::find(this->finalStates.begin(), this->finalStates.end(), line) == this->finalStates.end())
					{
						this->finalStates.push_back(line);
					}
					if (std::find(this->states.begin(), this->states.end(), line) == this->states.end())
					{
						this->states.push_back(line);
					}
				}
				else if (i == 2)
				{
					// transitions
					Transition transition(std::string(1, line[0]),
						std::string(1, line[1]),
						std::string(1, line[2]));
					this->transitions.push_back(transition);

					if (std::find(this->alphabet.begin(), this->alphabet.end(), std::string(1, line[1])) == this->alphabet.end())
					{
						this->alphabet.push_back(std::string(1, line[1]));
					}
				}
			
			}
		}
	}
}
