#include <iostream>
#include "FiniteAutomaton.hpp"


int main()
{
	FiniteAutomaton fa = FiniteAutomaton("identifiers.in");

	while (true)
	{
		std::cout << "Menu:\n1. States\n2. Alphabet\n3. Transitions\n4. Final states\n5. Is deterministic\n6. Check sequence\n";
		int choice;
		std::cout << "Choose:\n";
		std::cin >> choice;

		if (choice == 1)
		{
			fa.printStates();
			std::cout << "\n";
		}
		else if (choice == 2)
		{
			fa.printAlphabet();
			std::cout << "\n";
		}
		else if (choice == 3)
		{
			fa.printTransitions();
			std::cout << "\n";
		}
		else if (choice == 4)
		{
			fa.printFinalStates();
			std::cout << "\n";
		}
		else if (choice == 5)
		{
			fa.isDeterministic() ? std::cout << "Deterministic\n" : std::cout << "Nondeterministic\n";
		}
		else if (choice == 6)
		{
			std::cout << "Give sequence:\n";
			std::string sequence;
			std::cin >> sequence;
			
			fa.acceptsSequence(sequence) 
				? std::cout << "FA accepts sequence "<<sequence<<"\n" 
				: std::cout << "FA doesn't accept sequence " << sequence << "\n";
		}
		else
		{
			std::cout << "Invalid choice\n";
		}
	}
	
	return 0;
}