#pragma once
#include <string>

class Transition
{
private:
	std::string state1;
	std::string state2;
	std::string alphabetElem;

public:
	Transition(std::string state1, std::string state2, std::string terminal);
	std::string getState1();
	std::string getState2();
	std::string getAlphabetElem();

};

