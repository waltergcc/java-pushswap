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

typedef std::deque<info> stackDeque;

class PushSwap
{
	private:
		stackDeque	_stackA;
		stackDeque	_stackB;
		size_t		_maxID;

		// Constructor auxiliars
		void _checkInput(int ac, char **av);
		void _addNumber(int number);
		void _setStackIndex();

		// Moves
		void _sortSmall();
		void _sa();
		void _ra();
		void _rra();
		// void _sb();
		// void _ss();
		// void _pa();
		// void _pb();
		// void _rb();
		// void _rr();
		// void _rrb();
		// void _rrr();

		PushSwap();

	public:
		PushSwap(int ac, char **av);
		~PushSwap();

		void run();
		void print();
};