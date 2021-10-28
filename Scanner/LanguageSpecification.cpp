#include "LanguageSpecification.hpp"
#include <regex>
#include <fstream>

LanguageSpecification::LanguageSpecification()
{
	this->whiteSpaces = std::vector<std::string>();
	this->whiteSpaces.push_back(" ");
	this->whiteSpaces.push_back("\t");

	this->separators = std::vector<std::string>();
	this->operators = std::vector<std::string>();
	this->reservedWords = std::vector<std::string>();
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
		token += std::string(1, line[i]);
		if (!this->isPartOfOperator(token)) return startToken;
		if (this->isOperator(token)) return token;
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

void LanguageSpecification::loadTokens(std::string fileName)
{
	std::ifstream file(fileName, std::ios::in);
	if (file.is_open())
	{	
		for (int i = 0; i < 3; ++i)
		{
			std::string tokensNumber;
			getline(file, tokensNumber);
			std::string line;

			for (int j = 0; j < atoi(tokensNumber.c_str()); ++j)
			{
				getline(file, line);
				switch (i) 
				{
					case 0:
						this->separators.push_back(line);
						break;
					case 1:
						this->operators.push_back(line);
						break;
					case 2:
						this->reservedWords.push_back(line);
						break;
					default:
						break;
				}
			}
		}
	}
}

