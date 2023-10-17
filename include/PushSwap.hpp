#pragma once

#include "defines.hpp"

class PushSwap
{
	private:

		void _checkInput(int ac, char **av);
		PushSwap();

	public:
		PushSwap(int ac, char **av);
		~PushSwap();
};