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

static bool hasDuplicate(stackVector stack, int number)
{
	for (size_t i = 0; i < stack.size(); i++)
	{
		if (stack[i].number == number)
			return true;
	}
	return false;
}

static bool isSorted(stackVector s)
{
	for (stackVector::iterator it = s.begin(); it != s.end() - 1; it++)
	{
		if (it->number > (it + 1)->number)
			return false;
	}
	return true;
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
		this->_sa();
 	else if (this->_stackA.size() == 3)
		this->_sortSmall();
}

void PushSwap::print()
{
	for (stackVector::iterator it = this->_stackA.begin(); it != this->_stackA.end(); it++)
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
	this->_maxID = 0;

	for (size_t i = this->_stackA.size(); i > 0; i--)
	{
		stackVector::iterator	tmp;
		stackVector::iterator	it;
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
		if (tmp->index > this->_maxID)
			this->_maxID = tmp->index;
	}
}

// ---> Private Moves -----------------------------------------------------------

void	PushSwap::_sortSmall()
{
	if (this->_stackA[0].index == this->_maxID)
		this->_ra();
	else if (this->_stackA[1].index == this->_maxID)
		this->_rra();
	
	if (this->_stackA[0].index > this->_stackA[1].index)
		this->_sa();
}

void	PushSwap::_sa()
{
	info	tmp;

	tmp = this->_stackA[0];
	this->_stackA[0] = this->_stackA[1];
	this->_stackA[1] = tmp;

	std::cout << "sa" << std::endl;
}

void	PushSwap::_ra()
{
	info	tmp;

	tmp = this->_stackA[0];
	for (size_t i = 0; i < this->_stackA.size() - 1; i++)
	{
		this->_stackA[i] = this->_stackA[i + 1];
	}
	this->_stackA[this->_stackA.size() - 1] = tmp;

	std::cout << "ra" << std::endl;
}

void	PushSwap::_rra()
{
	info	tmp;

	tmp = this->_stackA[this->_stackA.size() - 1];
	for (size_t i = this->_stackA.size() - 1; i > 0; i--)
	{
		this->_stackA[i] = this->_stackA[i - 1];
	}
	this->_stackA[0] = tmp;

	std::cout << "rra" << std::endl;
}
