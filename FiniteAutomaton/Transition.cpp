#include "Transition.hpp"

Transition::Transition(std::string nonterminal1, std::string nonterminal2, std::string terminal)
    : state1{nonterminal1}, state2{nonterminal2}, alphabetElem{terminal}
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
