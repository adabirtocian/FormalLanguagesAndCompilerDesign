#include "SymbolTable.h"
#include <iostream>



int main()
{
	SymbolTable s = SymbolTable();
	s.add("ada"); // hashed to 94
	s.add("daa"); // hashed to 94
	s.add("d"); //hashed to 0
	s.add("123");

	std::cout <<"ada find at "<< s.find("ada")<<"\n";
	std::cout <<"daa find at "<< s.find("daa")<<"\n";
	std::cout <<"d find at "<< s.find("d")<<"\n";
	std::cout <<"123 find at "<< s.find("123")<<"\n";
	std::cout <<"1 find at "<< s.find("1")<<"\n";

	s.printAll();

	return 0;
}