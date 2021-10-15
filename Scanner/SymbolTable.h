#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class SymbolTable
{
private:
	std::vector<std::vector<std::string>> symbols;
    int hashFunction(std::string symbol);
    int tableSize;

public:
    SymbolTable();
    void add(std::string symbol);
    int find(std::string symbol);
    
};