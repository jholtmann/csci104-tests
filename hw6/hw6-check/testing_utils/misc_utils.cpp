#include "misc_utils.h"

#include <sys/resource.h>

#include <iostream>

void removeStackLimit()
{
	struct rlimit stack_limit;
	getrlimit(RLIMIT_STACK, &stack_limit);

	std::cout << "Stack size was " << stack_limit.rlim_cur << " bytes, setting it to the max of " <<
		(stack_limit.rlim_max == RLIM_INFINITY ? "infinity" : std::to_string(stack_limit.rlim_max)) << " bytes." << std::endl; 

	stack_limit.rlim_cur = stack_limit.rlim_max;
	setrlimit(RLIMIT_STACK, &stack_limit);
}