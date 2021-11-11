#include "Transition.hpp"

Transition::Transition(std::string state1, std::string alphabetElem, std::string state2)
    : state1{state1}, state2{state2}, alphabetElem{alphabetElem}
{}

std::string Transition::getState1()
{
    return this->state1;
}

std::string Transition::getState2()
{
    return this->state2;
}

std::string Transition::getAlphabetElem()
{
    return this->alphabetElem;
}
