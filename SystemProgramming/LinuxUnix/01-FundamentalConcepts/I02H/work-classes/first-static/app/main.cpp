#include <iostream>
#include <vector>
#include <iterator>
#include "hypernex_math.h"

int main()
{
	std::vector<int> a{1,2,3,4,5};
	std::vector<int> b{2,3,4,5,6};
	
	hypernex::add_vector(a, b);

	std::copy(a.begin(), a.end(), std::ostream_iterator<int>{std::cout, ", "});

	return EXIT_SUCCESS;
}


