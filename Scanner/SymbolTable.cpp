#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
    this->tableSize = 100;
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

int SymbolTable::find(std::string symbol)
{
    int hashValue = this->hashFunction(symbol);
    auto symbolsAtHasedValue = this->symbols[hashValue];

    for (int i = 0; i < symbolsAtHasedValue.size(); ++i)
    {
        if (symbolsAtHasedValue[i] == symbol)
        {
            return hashValue * 10 + i; //found
        }
    }
    return -1;
}

int SymbolTable::hashFunction(std::string symbol)
{
    string::iterator it;
    int sumAsciiCodes = 0;
    for (it = symbol.begin(); it != symbol.end(); it++) {
        sumAsciiCodes += int(*it);
    }

    return sumAsciiCodes % this->tableSize;
}
