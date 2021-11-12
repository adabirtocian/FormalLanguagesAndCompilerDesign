#include "FiniteAutomaton.hpp"
#include <fstream>
#include  <tuple>
#include <iostream>
#include <map>
#include <tuple>

FiniteAutomaton::FiniteAutomaton(std::string fileName)
	: states{std::set<std::string>()}, 
	initialState { std::string() },
	finalStates {std::set<std::string>()},
	transitions {std::vector<Transition>()},
	alphabet { std::set<std::string>()}
{
	this->deterministic = true;
	this->readFile(fileName);
}

std::set<std::string> FiniteAutomaton::getStates()
{
	return this->states;
}

std::string FiniteAutomaton::getInitialState()
{
	return this->initialState;
}

std::set<std::string> FiniteAutomaton::getFinalStates()
{
	return this->finalStates;
}

std::vector<Transition> FiniteAutomaton::getTransitions()
{
	return this->transitions;
}

std::set<std::string> FiniteAutomaton::getAlphabet()
{
	return this->alphabet;
}

bool FiniteAutomaton::isDeterministic()
{
	for (auto state : this->states)
	{
		std::map<std::tuple<std::string, std::string>, int> transitionsForCurrentState;
		for (auto transition : this->transitions)
		{
			if (transition.getState1() == state)
			{
				std::tuple<std::string, std::string> tuple(transition.getState1(), transition.getAlphabetElem());
				if (transitionsForCurrentState.find(tuple) != transitionsForCurrentState.end())
				{
					this->deterministic = true;
					return false;
				}
				else
				{
					transitionsForCurrentState.insert(std::pair<std::tuple<std::string, std::string>, int>(tuple, 0));
				}
			}
		}
	}

	return true;
}


bool FiniteAutomaton::acceptsSequenceRecursive(std::string sequence, int currentIdx, std::string currentState)
{
	if (currentIdx == sequence.length())
	{
		if (std::find(this->finalStates.begin(), this->finalStates.end(), currentState) != this->finalStates.end())
		{
			return true;
		}
		return false;
	}
	
	for (auto t : this->transitions)
	{
		if (t.getState1() == currentState && t.getAlphabetElem() == std::string(1, sequence[currentIdx]) and this->acceptsSequenceRecursive(sequence, currentIdx + 1, t.getState2()))
		{
			return true;
		}
	}
	return false;
}

bool FiniteAutomaton::acceptsSequence(std::string sequence)
{
	if (!this->deterministic)
	{
		return false;
	}

	return this->acceptsSequenceRecursive(sequence, 0, this->initialState);
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
		//initial state
		getline(file, this->initialState);
		this->states.insert(this->initialState);

		for (int i = 0; i < 2; ++i)
		{
			std::string categoryLen;
			getline(file, categoryLen);

			for (int j = 0; j < atoi(categoryLen.c_str()); ++j)
			{
				std::string line;
				getline(file, line);
				if (i == 0)
				{
					// final states
					this->finalStates.insert(line);
					this->states.insert(line);
				}
				else if (i == 1)
				{
					// transitions
					Transition transition(std::string(1, line[0]),
						std::string(1, line[1]),
						std::string(1, line[2]));
					if (!this->alreadyAddedTransition(transition))
					{
						this->transitions.push_back(transition);
					}
					this->alphabet.insert(transition.getAlphabetElem());
					this->states.insert(transition.getState2());
				}
			
			}
		}
	}
}

bool FiniteAutomaton::alreadyAddedTransition(Transition transition)
{
	for (auto t : this->transitions) 
	{
		if (t.getState1() == transition.getState1() && t.getAlphabetElem() == transition.getAlphabetElem()
			&& t.getState2() == transition.getState2()) return true;
	}
	return false;
}

