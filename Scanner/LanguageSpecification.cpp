#include "LanguageSpecification.hpp"
#include <regex>

LanguageSpecification::LanguageSpecification()
{
	this->whiteSpaces = std::vector<std::string>();
	this->whiteSpaces.push_back(" ");
	this->whiteSpaces.push_back("\t");

	this->separators = std::vector<std::string>();
	this->separators.push_back(",");
	this->separators.push_back(";");
	this->separators.push_back("(");
	this->separators.push_back(")");
	this->separators.push_back("[");
	this->separators.push_back("]");
	this->separators.push_back("{");
	this->separators.push_back("}");

	this->operators = std::vector<std::string>();
	this->operators.push_back("+");
	this->operators.push_back("-");
	this->operators.push_back("*");
	this->operators.push_back(":=");
	this->operators.push_back("<");
	this->operators.push_back("<=");
	this->operators.push_back(">");
	this->operators.push_back(">=");
	this->operators.push_back("=");
	this->operators.push_back("!=");
	this->operators.push_back("++");
	this->operators.push_back("--");

	this->reservedWords = std::vector<std::string>();
	this->reservedWords.push_back("if");
	this->reservedWords.push_back("else");
	this->reservedWords.push_back("and");
	this->reservedWords.push_back("or");
	this->reservedWords.push_back("not");
	this->reservedWords.push_back("read");
	this->reservedWords.push_back("write");
	this->reservedWords.push_back("const");
	this->reservedWords.push_back("array");
	this->reservedWords.push_back("int");
	this->reservedWords.push_back("char");
	this->reservedWords.push_back("string");
	this->reservedWords.push_back("bool");
	this->reservedWords.push_back("for");
	this->reservedWords.push_back("div");
	this->reservedWords.push_back("mod");
	this->reservedWords.push_back("true");
	this->reservedWords.push_back("false");

	this->encode();
}

std::map<std::string, int> LanguageSpecification::getCodes()
{
	return this->codes;
}

int LanguageSpecification::getCodeForToken(std::string token)
{
	return this->codes[token];
}

std::vector<std::string> LanguageSpecification::getSeparators()
{
	return this->separators;
}

std::vector<std::string> LanguageSpecification::getOperators()
{
	return this->operators;
}

std::vector<std::string> LanguageSpecification::getReservedWords()
{
	return this->reservedWords;
}

bool LanguageSpecification::isSeparator(std::string token)
{
	return std::find(this->separators.begin(), this->separators.end(), token) != this->separators.end();
}

bool LanguageSpecification::isWhiteSpace(std::string token)
{
	return std::find(this->whiteSpaces.begin(), this->whiteSpaces.end(), token) != this->whiteSpaces.end();
}

bool LanguageSpecification::isOperator(std::string token)
{
	return std::find(this->operators.begin(), this->operators.end(), token) != this->operators.end();;
}

bool LanguageSpecification::isReservedWord(std::string token)
{
	return std::find(this->reservedWords.begin(), this->reservedWords.end(), token) != this->reservedWords.end();;
}

bool LanguageSpecification::isIdentifier(std::string token)
{
	const std::regex identifierRegex("^[a-zA-Z]+[a-zA-Z0-9]{0,99}$");
	return std::regex_match(token, identifierRegex);
}

bool LanguageSpecification::isConstant(std::string token)
{
	const std::regex constantRegex("(^0|[+-]?[1-9]+[0-9]*$)|(^'[a-zA-Z0-9 #&^%]{1,1}'$)|(^\"[a-zA-Z0-9 #&^%]{2,99}\"$)"); //ToDo
	return std::regex_match(token, constantRegex);
}

bool LanguageSpecification::isPartOfOperator(std::string token)
{
	for (auto op : this->operators)
	{
		if (op.find(token) != std::string::npos)
		{
			return true;
		}
	}
	return false;
}

std::string LanguageSpecification::getOperatorToken(std::string startToken, std::string line, int index)
{
	std::string token = startToken;
	for (int i = index; i < line.size(); ++i)
	{
		if (!this->isPartOfOperator(std::string(1, line[i])))
		{
			return token;
		}
		token += std::string(1, line[i]);
	}
	return token;
}

std::string LanguageSpecification::getStringToken(std::string line, int index)
{
	std::string token = "\"";
	int charsCount = 0;
	while (index < line.size() and line[index] != '"')
	{
		token += std::string(1, line[index]);
		++charsCount;
		++index;
	}
	token += "\"";
	return token;
}

void LanguageSpecification::encode()
{
	this->codes = std::map<std::string, int>();
	this->codes.insert(std::pair<std::string, int>("identifier", 0));
	this->codes.insert(std::pair<std::string, int>("constant", 1));

	int currentCode = 2;
	for (int i = 0; i < this->separators.size(); ++i)
	{
		this->codes.insert(std::pair<std::string, int>(this->separators[i], currentCode));
		currentCode++;
	}
	for (int i = 0; i < this->operators.size(); ++i)
	{
		this->codes.insert(std::pair<std::string, int>(this->operators[i], currentCode));
		currentCode++;
	}
	for (int i = 0; i < this->reservedWords.size(); ++i)
	{
		this->codes.insert(std::pair<std::string, int>(this->reservedWords[i], currentCode));
		currentCode++;
	}
}

