#pragma once
#include <vector>
#include <string>
#include <set>
#include "Transition.hpp"


class FiniteAutomaton
{
private:
	std::set<std::string> states;
	std::string initialState;
	std::set<std::string> finalStates;
	std::vector<Transition> transitions;
	std::set<std::string> alphabet;
	bool deterministic;


	void readFile(std::string fileName);
	bool alreadyAddedTransition(Transition transition);
	bool acceptsSequenceRecursive(std::string sequence, int currentIdx, std::string currentState);

public:
	FiniteAutomaton(std::string fileName);
	std::set<std::string> getStates();
	std::string getInitialState();
	std::set<std::string> getFinalStates();
	std::vector<Transition> getTransitions();
	std::set<std::string> getAlphabet();

	bool isDeterministic();
	bool acceptsSequence(std::string sequence);

	void printStates();
	void printAlphabet();
	void printTransitions();
	void printFinalStates();
	
};

