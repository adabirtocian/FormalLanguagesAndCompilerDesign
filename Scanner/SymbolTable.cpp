#include "SymbolTable.hpp"
#include <fstream>
#include <iostream>
#include <string>

SymbolTable::SymbolTable(): tableSize(100), noElements(0), noElementsList(10)
{
    this->symbols = std::vector<std::vector<std::string>>(this->tableSize);
    for (int i = 0; i < this->tableSize; ++i)
        this->symbols[i] = std::vector<std::string>();
}

void SymbolTable::add(std::string symbol)
{
    int hashValue = this->hashFunction(symbol); 
    if (this->find(symbol) == -1)
    { 
        if (this->symbols[hashValue].size() < 10)
        {
            this->symbols[hashValue].push_back(symbol);
        }
    }
}

int SymbolTable::getNoElementsInFront(int hashTableEntry)
{
    int noElements = 0;
    for (int i = 0; i < hashTableEntry; ++i)
    {
        noElements += this->symbols[i].size();
    }
    return noElements;
}

int SymbolTable::find(std::string symbol)
{
    int hashValue = this->hashFunction(symbol);
    auto symbolsAtHasedValue = this->symbols[hashValue];

    for (int i = 0; i < symbolsAtHasedValue.size(); ++i)
    {
        if (symbolsAtHasedValue[i] == symbol)
        {
            return this->noElementsList * hashValue + i; //found
        }
    }
    return -1;
}

void SymbolTable::printAll()
{
    std::cout << "Symbol table\n";
    for (int i = 0; i < this->tableSize; ++i)
    {
        if (this->symbols[i].size() > 0)
        {
            std::cout << "=====" << i << "===== \n";
            for (int j = 0; j < this->symbols[i].size(); ++j)
            {
                if (!this->symbols[i][j].empty())
                {
                    std::cout << "(" << this->symbols[i][j] << ", " << this->find(this->symbols[i][j]) << ")\n";
                }
            }
            std::cout << "\n";
        }   
    }
}

void SymbolTable::writeToFile(std::string fileName)
{
    std::ofstream file(fileName, std::ios::out);
    if (file.is_open())
    {
        for (int i = 0; i < this->tableSize; ++i)
        {
            if (this->symbols[i].size() > 0)
            {
                file << "=====" << i << "===== \n";
                for (int j = 0; j < this->symbols[i].size(); ++j)
                {
                    if (!this->symbols[i][j].empty())
                    {
                        file << "(" << this->symbols[i][j] << ", " << this->find(this->symbols[i][j]) << ")\n";
                    }
                }
                file << "\n";
            }
        }
    }
}

int SymbolTable::hashFunction(std::string symbol)
{
    std::string::iterator it;
    int sumAsciiCodes = 0;
    for (it = symbol.begin(); it != symbol.end(); it++) {
        sumAsciiCodes += int(*it);
    }

    return sumAsciiCodes % this->tableSize;
}
