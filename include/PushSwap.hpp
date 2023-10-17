#pragma once

#include "defines.hpp"

class PushSwap
{
	private:
		intVector	_numbers;
		
		void _checkInput(int ac, char **av);

		PushSwap();

	public:
		PushSwap(int ac, char **av);
		~PushSwap();
};