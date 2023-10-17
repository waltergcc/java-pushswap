#pragma once

#include "defines.hpp"

struct info
{
	int		number;
	size_t	index;
	int		pos;
	int		whereFit;
	int		movesInA;
	int		movesInB;
};

typedef std::vector<info> stackVector;

class PushSwap
{
	private:
		stackVector	_stackA;
		stackVector	_stackB;

		// Constructor auxiliars
		void _checkInput(int ac, char **av);
		void _addNumber(int number);
		void _setStackIndex();

		// Moves
		void _sa();
		// void _sb();
		// void _ss();
		// void _pa();
		// void _pb();
		// void _ra();
		// void _rb();
		// void _rr();
		// void _rra();
		// void _rrb();
		// void _rrr();

		PushSwap();

	public:
		PushSwap(int ac, char **av);
		~PushSwap();

		void run();
		void print();
};