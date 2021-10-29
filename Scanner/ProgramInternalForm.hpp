#pragma once
#include <map>
#include <vector>
#include <string>

class ProgramInternalForm
{
private:
	std::vector<std::pair<std::string, int>> programInternalForm;

public:
	ProgramInternalForm();
	void add(std::pair<std::string, int> entry);
	std::vector<std::pair<std::string, int>> getProgramInternalForm();
	void printAll();
	void writeToFile(std::string fileName);
};

