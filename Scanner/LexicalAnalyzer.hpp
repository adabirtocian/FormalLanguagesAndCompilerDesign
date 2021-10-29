#pragma once
#include "LanguageSpecification.hpp"
#include "ProgramInternalForm.hpp"
#include "SymbolTable.hpp"

class LexicalAnalyzer
{
private:
	LanguageSpecification& language;
	ProgramInternalForm& pif;
	SymbolTable& symbolTable;

	std::vector<std::string> splitIntoTokens(std::string line);
	void addTokenAccumulator(std::string& tokenAccumulator, std::vector<std::string>& tokens);
public:
	LexicalAnalyzer(LanguageSpecification& language, ProgramInternalForm& pif, SymbolTable& symbolTable);
	void scanningAlgo(std::string fileName);
	std::vector<std::string> getInputAsTokensList(std::string fileName);
	ProgramInternalForm& getPif();
	SymbolTable& getSt();
};

