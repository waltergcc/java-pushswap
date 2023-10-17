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

// ---> Constructor and destructor ----------------------------------------------

PushSwap::PushSwap(int ac, char **av)
{
	this->_checkInput(ac, av);
}

PushSwap::~PushSwap(){}

// ---> Private constructor auxiliars ------------------------------------------

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
