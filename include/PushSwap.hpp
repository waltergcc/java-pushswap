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

		void _checkInput(int ac, char **av);
		void _addNumber(int number);
		void _setStackIndex();

		PushSwap();

	public:
		PushSwap(int ac, char **av);
		~PushSwap();
};