#include "ProgramInternalForm.hpp"
#include <iostream>
#include <fstream>

ProgramInternalForm::ProgramInternalForm(): programInternalForm{ std::vector<std::pair<std::string, int>>() }
{}

void ProgramInternalForm::add(std::pair<std::string, int> entry)
{
	this->programInternalForm.push_back(entry);
}

std::vector<std::pair<std::string, int>> ProgramInternalForm::getProgramInternalForm()
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

void ProgramInternalForm::writeToFile(std::string fileName)
{
	std::ofstream file(fileName, std::ios::out);
	if (file.is_open())
	{
		for (auto pair : this->programInternalForm)
		{
			file << pair.first << " -- " << pair.second << "\n";
		}
	}
}
