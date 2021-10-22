#include "ProgramInternalForm.hpp"
#include <iostream>

ProgramInternalForm::ProgramInternalForm(): programInternalForm{ std::vector<std::pair<int, int>>() }
{}

void ProgramInternalForm::add(std::pair<int, int> entry)
{
	this->programInternalForm.push_back(entry);
}

std::vector<std::pair<int, int>> ProgramInternalForm::getProgramInternalForm()
{
	return this->programInternalForm;
}

void ProgramInternalForm::printAll()
{
	std::cout << "Program internal form\n";
	for (auto pair : this->programInternalForm)
	{
		std::cout << "(" << pair.first << "," << pair.second << ")\n";
 	}
}
