#pragma once
#include <map>
#include <vector>

class ProgramInternalForm
{
private:
	std::vector<std::pair<int, int>> programInternalForm;

public:
	ProgramInternalForm();
	void add(std::pair<int, int> entry);
	std::vector<std::pair<int, int>> getProgramInternalForm();
	void printAll();
};

