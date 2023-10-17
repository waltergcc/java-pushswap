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

// ---> Constructor and destructor ----------------------------------------------

PushSwap::PushSwap(int ac, char **av)
{
	this->_checkInput(ac, av);
}

PushSwap::~PushSwap(){}

// ---> Private constructor auxiliars ------------------------------------------

void PushSwap::_checkInput(int ac, char **av)
{
	intVector::iterator	it;
	double		tmp;

	if (ac < 2)
		throw std::runtime_error("Error: no arguments");
	
	for (int i = 1; i < ac; i++)
	{
		if (!isValidNumber(av[i]))
			throw std::runtime_error("Error: invalid argument" + std::string(av[i]));

		tmp = std::atof(av[i]);
		if (tmp > INT_MAX || tmp < INT_MIN)
			throw std::runtime_error("Error: argument out of range " + std::string(av[i]));
		
		it = std::find(this->_numbers.begin(), this->_numbers.end(), tmp);
		if (it != this->_numbers.end())
			throw std::runtime_error("Error: duplicate argument " + std::string(av[i]));

		this->_numbers.push_back(tmp);
	}
	if (this->_numbers.size() < 2)
		throw std::runtime_error("Error: not enough arguments");
}
