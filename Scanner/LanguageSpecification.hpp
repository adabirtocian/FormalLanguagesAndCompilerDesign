#pragma once
#include <vector>
#include <string>
#include <map>

class LanguageSpecification
{
private:
	std::vector<std::string> separators;
	std::vector<std::string> operators;
	std::vector<std::string> reservedWords;
	std::vector<std::string> whiteSpaces;

public:
	LanguageSpecification();
	std::vector<std::string> getSeparators();
	std::vector<std::string> getOperators();
	std::vector<std::string> getReservedWords();
	
	bool isSeparator(std::string token);
	bool isWhiteSpace(std::string token);
	bool isOperator(std::string token);
	bool isReservedWord(std::string token);
	bool isIdentifier(std::string token);
	bool isConstant(std::string token);
	bool isPartOfOperator(std::string token);

	std::string getOperatorToken(std::string startToken, std::string line, int index);
	std::string getStringToken(std::string line, int index);

	void loadTokens(std::string fileName);
};

