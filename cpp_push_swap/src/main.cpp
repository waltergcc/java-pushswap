#include "PushSwap.hpp"

int main(int ac, char **av)
{
	try
	{
		PushSwap pushswap(ac, av);
		pushswap.run();
		pushswap.printList(true);
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}