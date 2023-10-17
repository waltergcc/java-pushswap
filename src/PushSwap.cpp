#include "PushSwap.hpp"

PushSwap::PushSwap(int ac, char **av)
{
	this->_checkInput(ac, av);
}

PushSwap::~PushSwap()
{
}

void PushSwap::_checkInput(int ac, char **av)
{
	if (ac < 2)
		throw std::runtime_error("Error: no arguments");
	
	for (int i = 1; i < ac; i++)
	{
		std::cout << av[i] << std::endl;
	}
}
