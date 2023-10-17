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
	std::cout << "Stack A: ";
	for (stackDeque::iterator it = this->_stackA.begin(); it != this->_stackA.end(); it++)
	{
		std::cout << it->number << " ";
	}
	std::cout << std::endl;
	std::cout << "Stack B: ";
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

// ---> Private Moves -----------------------------------------------------------

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

void	PushSwap::_sortBig()
{
	this->_pushAllSave3();
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