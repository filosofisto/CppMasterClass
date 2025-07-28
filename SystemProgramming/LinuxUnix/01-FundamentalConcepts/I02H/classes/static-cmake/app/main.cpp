#include <iostream>
#include <vector>
#include <iterator>
#include "hypernex_math.h"

int main()
{
	std::vector a{1,2,3,4,5};
	std::vector b{1,2,3,4,5};

	hypernex::add_vector(a, b);

	std::copy(a.begin(), a.end(), std::ostream_iterator<int>{std::cout, ", "});

	return EXIT_SUCCESS;
}
