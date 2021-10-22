#include <iostream>
#include "LanguageSpecification.hpp"
#include "SymbolTable.hpp"
#include "ProgramInternalForm.hpp"
#include "LexicalAnalyzer.hpp"

int main()
{
	LanguageSpecification language = LanguageSpecification();
	auto codes = language.getCodes();
	//std::cout << language.isConstant("+21"); //1
	//std::cout << language.isConstant("-8"); //1
	//std::cout << language.isConstant("'f'"); //1
	//std::cout << language.isConstant("'fff'"); //0
	//std::cout << language.isConstant("\"dsds\""); //1
	//std::cout << language.isConstant("123"); //1
	//std::cout << language.isConstant("4"); //1
	//std::cout << language.isConstant("'0'"); //1
	//std::cout << language.isConstant("\"s21\""); //1
	//std::cout << language.isConstant("\"# e\""); //1

	ProgramInternalForm pif = ProgramInternalForm();
	SymbolTable symbolTable = SymbolTable();
	LexicalAnalyzer lexicalAnalyzer = LexicalAnalyzer(language, pif, symbolTable);
	auto tokens = lexicalAnalyzer.getInputAsTokensList("input3.txt");
	for (auto t : tokens)
	{
		std::cout << t << "|";
	}
	std::cout << std::endl;
	try {
		lexicalAnalyzer.scanningAlgo("input3.txt");
		std::cout << "Lexically corect\n";
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	pif.printAll();
	std::cout << std::endl;
	symbolTable.printAll();
	for (auto c : language.getCodes())
	{
		std::cout << c.first << " -> " << c.second << "\n";
	}

	return 0;
}