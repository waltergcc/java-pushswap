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

		// Constructor auxiliars
		void _checkInput(int ac, char **av);
		void _addNumber(int number);
		void _setStackIndex();

		// sort Big Moves auxiliars
		void	_sortBig();
		void	_pushAllSave3();
		void	_WhereItFitInA();
		int		_getTargetPosition(size_t index);
		void	_calculateMoves();
		void	_doMoves();
		void	_rotateBoth(int &movesInA, int &movesInB);
		void	_reverseBoth(int &movesInA, int &movesInB);
		void	_rotateA(int &movesInA);
		void	_rotateB(int &movesInB);
		void	_lastSort();

		// Moves
		void _sortSmall();
		void _sa(bool print);
		void _ra(bool print);
		void _rra(bool print);
		void _sb(bool print);
		void _rb(bool print);
		void _rrb(bool print);
		void _ss();
		void _rr();
		void _rrr();
		void _pa();
		void _pb();

		PushSwap();

	public:
		PushSwap(int ac, char **av);
		~PushSwap();

		void run();
		void printList(bool sorted);
};