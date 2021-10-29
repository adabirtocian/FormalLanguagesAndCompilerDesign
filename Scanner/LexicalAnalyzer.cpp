#include "LexicalAnalyzer.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

LexicalAnalyzer::LexicalAnalyzer(LanguageSpecification& language, ProgramInternalForm& pif, SymbolTable& symbolTable): 
	language(language), pif(pif), symbolTable(symbolTable)
{}

void LexicalAnalyzer::scanningAlgo(std::string fileName)
{
	std::ifstream file(fileName, std::ios::in);
	if (file.is_open())
	{
		std::string line;
		int lineIdx = 1;
		while (getline(file, line))
		{
			std::vector<std::string> tokens = this->splitIntoTokens(line);
			for (std::string token : tokens)
			{
				if (this->language.isReservedWord(token) || this->language.isOperator(token) || this->language.isSeparator(token))
				{
					this->pif.add(std::pair<std::string, int>(token, -1));
				}
				else if (this->language.isIdentifier(token))
				{
					this->symbolTable.add(token);
					int positionInST = this->symbolTable.find(token);
					this->pif.add(std::pair<std::string, int>("id", positionInST));
				}
				else if (this->language.isConstant(token))
				{
					this->symbolTable.add(token);
					int positionInST = this->symbolTable.find(token);
					this->pif.add(std::pair<std::string, int>("constant", positionInST));
				}
				else
				{
					throw std::exception(("Lexical error at line " + std::to_string(lineIdx) + " token " + token).c_str());
				}
			}
			lineIdx++;
		}
	}
}

std::vector<std::string> LexicalAnalyzer::getInputAsTokensList(std::string fileName)
{
	std::vector<std::string> tokens = std::vector<std::string>();
	std::ifstream file(fileName, std::ios::in);
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			std::vector<std::string> lineTokens = this->splitIntoTokens(line);
			tokens.insert(tokens.end(), lineTokens.begin(), lineTokens.end());
		}
	}
	return tokens;
}

ProgramInternalForm& LexicalAnalyzer::getPif()
{
	return this->pif;
}

SymbolTable& LexicalAnalyzer::getSt()
{
	return this->symbolTable;
}

std::vector<std::string> LexicalAnalyzer::splitIntoTokens(std::string line)
{
	std::vector<std::string> tokens = std::vector<std::string>();
	std::string tokenAccumulator = "";

	for (int i = 0; i < line.size(); ++i)
	{
		if (!this->language.isWhiteSpace(std::string(1, line[i])))
		{
			if (this->language.isSeparator(std::string(1, line[i])))
			{
				this->addTokenAccumulator(tokenAccumulator, tokens);
				tokens.push_back(std::string(1, line[i]));
			}
			else if (this->language.isPartOfOperator(std::string(1, line[i])))
			{
				this->addTokenAccumulator(tokenAccumulator, tokens);
				std::string operatorToken = this->language.getOperatorToken(std::string(1, line[i]), line, i + 1);
				if ((operatorToken == "+" || operatorToken == "-") && (tokens[tokens.size() - 1] == ":=" || tokens[tokens.size() -1] == "("))
				{
					tokenAccumulator += operatorToken;
				}
				else
				{
					i += operatorToken.length() - 1;
					tokens.push_back(operatorToken);
				}
			}
			else if (line[i] == '"')
			{
				this->addTokenAccumulator(tokenAccumulator, tokens);
				std::string stringToken = this->language.getStringToken(line, i + 1);
				i += stringToken.size() - 1;
				tokens.push_back(stringToken);
			}
			else
			{
				tokenAccumulator += std::string(1, line[i]);
			}
		}
		else 
		{
			this->addTokenAccumulator(tokenAccumulator, tokens);
		}
	}
	return tokens;
}

void LexicalAnalyzer::addTokenAccumulator(std::string& tokenAccumulator, std::vector<std::string>& tokens)
{
	if (tokenAccumulator.size() != 0 && tokenAccumulator != " ")
	{
		if (tokenAccumulator == "+0" || tokenAccumulator == "-0")
		{
			tokenAccumulator = tokenAccumulator[1];
		}

		tokens.push_back(tokenAccumulator);
		tokenAccumulator = "";
	}

}
