#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include "Transition.hpp"

class FiniteAutomaton
{
private:
	std::vector<std::string> states;
	std::string initialState;
	std::vector<std::string> finalStates;
	std::vector<Transition> transitions;
	std::vector<std::string> alphabet;
	bool deterministic;

	void readFile(std::string fileName);

public:
	FiniteAutomaton(std::string fileName);
	std::vector<std::string> getStates();
	std::string getInitialState();
	std::vector<std::string> getFinalStates();
	std::vector<Transition> getTransitions();
	std::vector<std::string> getAlphabet();

	bool isDeterministic();
	bool acceptsSequence(std::string sequence);

	void printStates();
	void printAlphabet();
	void printTransitions();
	void printFinalStates();
	
};

