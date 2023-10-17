#include "main.hpp"

int main(int ac, char **av)
{
	try
	{
		PushSwap pushswap(ac, av);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}