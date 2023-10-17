#include "PushSwap.hpp"

// ---> Static functions -------------------------------------------------------

static bool isValidNumber(std::string s)
{
	for (size_t i = 0; i < s.length(); i++)
	{
		if (i == 0 && (s[i] == '-' || s[i] == '+'))
			continue;
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

static bool hasDuplicate(stackDeque stack, int number)
{
	for (size_t i = 0; i < stack.size(); i++)
	{
		if (stack[i].number == number)
			return true;
	}
	return false;
}

static bool isSorted(stackDeque s)
{
	for (stackDeque::iterator it = s.begin(); it != s.end() - 1; it++)
	{
		if (it->number > (it + 1)->number)
			return false;
	}
	return true;
}

static size_t getMaxID(stackDeque s)
{
	size_t	max = 0;

	for (stackDeque::iterator it = s.begin(); it != s.end(); it++)
	{
		if (it->index > max)
			max = it->index;
	}
	return max;
}

static void getCurrentPositions(stackDeque &s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		s[i].pos = i;
	}
}

static size_t getLowerPosition(stackDeque s)
{
	size_t	minIndex = INT_MAX;
	getCurrentPositions(s);

	size_t lowPosistion = s.front().pos;
	for (stackDeque::iterator it = s.begin(); it != s.end(); it++)
	{
		if (it->index < minIndex)
		{
			minIndex = it->index;
			lowPosistion = it->pos;
		}
	}
	return lowPosistion;
}

// ---> Constructor and destructor ----------------------------------------------

PushSwap::PushSwap(int ac, char **av)
{
	this->_checkInput(ac, av);
	this->_setStackIndex();
}

PushSwap::~PushSwap(){}

// ---> public member functions -------------------------------------------------

void PushSwap::run()
{
	if (isSorted(this->_stackA))
		throw std::runtime_error("List is already sorted");

	if (this->_stackA.size() == 2)
		this->_sa(true);
 	else if (this->_stackA.size() == 3)
		this->_sortSmall();
	else
		this->_sortBig();
}

void PushSwap::print()
{
	for (stackDeque::iterator it = this->_stackA.begin(); it != this->_stackA.end(); it++)
	{
		std::cout << it->number << " ";
	}
	std::cout << std::endl;
	for (stackDeque::iterator it = this->_stackB.begin(); it != this->_stackB.end(); it++)
	{
		std::cout << it->number << " ";
	}

	std::cout << std::endl;
}

// ---> Private Cnstructor auxiliars ------------------------------------------

void PushSwap::_checkInput(int ac, char **av)
{
	double					number;

	if (ac < 2)
		throw std::runtime_error("Error: no arguments");
	
	for (int i = 1; i < ac; i++)
	{
		if (!isValidNumber(av[i]))
			throw std::runtime_error("Error: invalid argument" + std::string(av[i]));

		number = std::atof(av[i]);
		if (number > INT_MAX || number < INT_MIN)
			throw std::runtime_error("Error: argument out of range " + std::string(av[i]));
		
		if (hasDuplicate(this->_stackA, number))
			throw std::runtime_error("Error: duplicate argument " + std::string(av[i]));
		
		this->_addNumber(number);
	}
	if (this->_stackA.size() < 2)
		throw std::runtime_error("Error: not enough arguments");
}

void PushSwap::_addNumber(int number)
{
	info	tmp;

	tmp.number = number;
	tmp.index = 0;
	tmp.pos = -1;
	tmp.whereFit = -1;
	tmp.movesInA = -1;
	tmp.movesInB = -1;

	this->_stackA.push_back(tmp);
}

void PushSwap::_setStackIndex()
{
	for (size_t i = this->_stackA.size(); i > 0; i--)
	{
		stackDeque::iterator	tmp;
		stackDeque::iterator	it;
		int	max = INT_MIN;
		for (it = this->_stackA.begin(); it != this->_stackA.end(); it++)
		{
			if (it->index == 0 && it->number > max)
			{
				max = it->number;
				tmp = it;
			}
		}
		tmp->index = i;
	}
}

// ---> Sort Big auxiliars -----------------------------------------------------------

void	PushSwap::_sortBig()
{
	this->_pushAllSave3();

	while (!this->_stackB.empty())
	{
		this->_WhereItFitInA();
		this->_calculateMoves();
		this->_doMoves();
	}
	if (!isSorted(this->_stackA))
		this->_lastSort();
}

void	PushSwap::_pushAllSave3()
{
	size_t	size = this->_stackA.size();
	size_t	moves = 0;

	for (size_t i = 0; size > 6 && i < size && moves < size / 2; i++)
	{
		if (this->_stackA.front().index <= size / 2)
		{
			this->_pb();
			moves++;
		}
		else
			this->_ra(true);
	}

	for (; size - moves > 3; moves++)
		this->_pb();
	
	this->_sortSmall();
}

void	PushSwap::_WhereItFitInA()
{
	getCurrentPositions(this->_stackA);
	getCurrentPositions(this->_stackB);

	for (stackDeque::iterator it = this->_stackB.begin(); it != this->_stackB.end(); it++)
	{
		it->whereFit = this->_getTargetPosition(it->index);
	}
}

int		PushSwap::_getTargetPosition(size_t index)
{
	size_t max = INT_MAX;
	int position = -1;

	for (stackDeque::iterator it = this->_stackA.begin(); it != this->_stackA.end(); it++)
	{
		if (it->index > index && it->index < max)
		{
			max = it->index;
			position = it->pos;
		}
	}
	if (max != INT_MAX)
		return position;

	for (stackDeque::iterator it = this->_stackA.begin(); it != this->_stackA.end(); it++)
	{
		if (it->index < max)
		{
			max = it->index;
			position = it->pos;
		}
	}
	return position;
}

void	PushSwap::_calculateMoves()
{
	int sizeA = this->_stackA.size();
	int sizeB = this->_stackB.size();

	for (stackDeque::iterator it = this->_stackB.begin(); it != this->_stackB.end(); it++)
	{
		it->movesInB = it->pos;
		if (it->pos > sizeB / 2)
			it->movesInB = (sizeB - it->pos) * -1;
		it->movesInA = it->whereFit;
		if (it->whereFit > sizeA / 2)
			it->movesInA = (sizeA - it->whereFit) * -1;
	}
}

void	PushSwap::_doMoves()
{
	size_t less = INT_MAX;
	int		movesInA = 0;
	int		movesInB = 0;

	for (stackDeque::iterator it = this->_stackB.begin(); it != this->_stackB.end(); it++)
	{
		if (abs(it->movesInA) + abs(it->movesInB) < abs(less))
		{
			less = abs(it->movesInA) + abs(it->movesInB);
			movesInA = it->movesInA;
			movesInB = it->movesInB;
		}
	}

	// std::cout << "-----------------------------------	" << std::endl;
	if (movesInA < 0 && movesInB < 0)
		this->_reverseBoth(movesInA, movesInB);
	else if (movesInA > 0 && movesInB > 0)
		this->_rotateBoth(movesInA, movesInB);
	this->_rotateA(movesInA);
	this->_rotateB(movesInB);
	// std::cout << "outMA: " << movesInA << " outMB: " << movesInB << std::endl;

	this->_pa();
}

void	PushSwap::_reverseBoth(int &movesInA, int &movesInB)
{
	// std::cout << "InRRR: " << movesInA << " " << movesInB << std::endl;
	while (movesInA < 0 && movesInB < 0)
	{
		movesInA++;
		movesInB++;
		this->_rrr();
	}
}

void	PushSwap::_rotateBoth(int &movesInA, int &movesInB)
{
	// std::cout << "InRR: " << movesInA << " " << movesInB << std::endl;
	while (movesInA > 0 && movesInB > 0)
	{
		movesInA--;
		movesInB--;
		this->_rr();
	}
}

void	PushSwap::_rotateA(int &movesInA)
{
	// std::cout << "InRA: " << movesInA << std::endl;
	while (movesInA)
	{
		if (movesInA > 0)
		{
			movesInA--;
			this->_ra(true);
		}
		else if (movesInA < 0)
		{
			movesInA++;
			this->_rra(true);
		}
	}
}

void	PushSwap::_rotateB(int &movesInB)
{
	// std::cout << "InRB: " << movesInB << std::endl;
	while (movesInB > 0)
	{
		if (movesInB > 0)
		{
			movesInB--;
			this->_rb(true);
		}
		else if (movesInB < 0)
		{
			movesInB++;
			this->_rrb(true);
		}
	}
}

void	PushSwap::_lastSort()
{
	size_t size = this->_stackA.size();
	size_t position = getLowerPosition(this->_stackA);

	if (position > size / 2)
	{
		while (position++ < size)
			this->_rra(true);
	}
	else
	{
		while (position--)
			this->_ra(true);
	}
}

// ---> Common Moves auxiliars -----------------------------------------------------------

void	PushSwap::_sortSmall()
{
	if (isSorted(this->_stackA))
		return;

	size_t maxID = getMaxID(this->_stackA);

	if (this->_stackA[0].index == maxID)
		this->_ra(true);
	else if (this->_stackA[1].index == maxID)
		this->_rra(true);
	
	if (this->_stackA[0].index > this->_stackA[1].index)
		this->_sa(true);
}

void	PushSwap::_sa(bool print)
{
	info	tmp;

	tmp = this->_stackA[0];
	this->_stackA[0] = this->_stackA[1];
	this->_stackA[1] = tmp;

	if (print)
		std::cout << "sa" << std::endl;
}

void	PushSwap::_ra(bool print)
{
	info	tmp;

	tmp = this->_stackA.front();
	this->_stackA.pop_front();
	this->_stackA.push_back(tmp);

	if (print)
		std::cout << "ra" << std::endl;
}

void	PushSwap::_rra(bool print)
{
	info	tmp;

	tmp = this->_stackA.back();
	this->_stackA.pop_back();
	this->_stackA.push_front(tmp);

	if (print)
		std::cout << "rra" << std::endl;
}

void	PushSwap::_sb(bool print)
{
	info	tmp;

	tmp = this->_stackB[0];
	this->_stackB[0] = this->_stackB[1];
	this->_stackB[1] = tmp;

	if (print)
		std::cout << "sb" << std::endl;
}

void	PushSwap::_rb(bool print)
{
	info	tmp;

	tmp = this->_stackB.front();
	this->_stackB.pop_front();
	this->_stackB.push_back(tmp);

	if (print)
		std::cout << "rb" << std::endl;
}

void	PushSwap::_rrb(bool print)
{
	info	tmp;

	tmp = this->_stackB.back();
	this->_stackB.pop_back();
	this->_stackB.push_front(tmp);
	
	if (print)
		std::cout << "rrb" << std::endl;
}

void	PushSwap::_ss()
{
	this->_sa(false);
	this->_sb(false);
	std::cout << "ss" << std::endl;
}

void	PushSwap::_rr()
{
	this->_ra(false);
	this->_rb(false);
	std::cout << "rr" << std::endl;
}

void	PushSwap::_rrr()
{
	this->_rra(false);
	this->_rrb(false);
	std::cout << "rrr" << std::endl;
}

void	PushSwap::_pa()
{
	info	tmp;

	tmp = this->_stackB.front();
	this->_stackB.pop_front();
	this->_stackA.push_front(tmp);

	std::cout << "pa" << std::endl;
}

void	PushSwap::_pb()
{
	info	tmp;

	tmp = this->_stackA.front();
	this->_stackA.pop_front();
	this->_stackB.push_front(tmp);

	std::cout << "pb" << std::endl;
}