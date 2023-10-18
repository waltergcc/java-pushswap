#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <deque>
#include <climits>
#include <cstdlib>
#include <algorithm>
#include <ctime>

#define CLEAR				"\033c"

#define ALREADY_SORTED		"List is already sorted"
#define NO_ARGUMENTS		"Error: no arguments"
#define INVALID_ARG(arg)	"Error: invalid argument " + arg
#define OVERFLOW(arg)		"Error: out of range argument " + arg
#define DUPLICATE_ARG(arg)	"Error: duplicate argument " + arg
#define NOT_ENOUGH_ARGS		"Error: not enough arguments"