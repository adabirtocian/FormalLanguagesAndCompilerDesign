#include <iostream>
#include "LanguageSpecification.hpp"
#include "SymbolTable.hpp"
#include "ProgramInternalForm.hpp"
#include "LexicalAnalyzer.hpp"

int main()
{
	const std::string INPUT_FILE = "input2.txt";
	const std::string TOKENS_FILE_NAME = "tokens.in";


	LanguageSpecification language = LanguageSpecification();
	language.loadTokens(TOKENS_FILE_NAME);

	ProgramInternalForm pif = ProgramInternalForm();
	SymbolTable symbolTable = SymbolTable();
	LexicalAnalyzer lexicalAnalyzer = LexicalAnalyzer(language, pif, symbolTable);
	auto tokens = lexicalAnalyzer.getInputAsTokensList(INPUT_FILE);
	for (auto t : tokens)
	{
		std::cout << t << "|";
	}
	std::cout << std::endl;

	try {
		lexicalAnalyzer.scanningAlgo(INPUT_FILE);
		std::cout << "Lexically corect\n";
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	pif.writeToFile("pif.out");
	symbolTable.writeToFile("symbolTable.out");

	return 0;
}