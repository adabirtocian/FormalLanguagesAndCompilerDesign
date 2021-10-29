#pragma once
#include <vector>
#include <string>

class SymbolTable
{
private:
	std::vector<std::vector<std::string>> symbols;
    int hashFunction(std::string symbol);
    int tableSize;
    int noElements;
    int noElementsList;

    int getNoElementsInFront(int hashTableEntry);

public:
    SymbolTable();
    void add(std::string symbol);
    int find(std::string symbol);
    void printAll();
    void writeToFile(std::string fileName);
    
};