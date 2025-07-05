#include <iostream>
#include <vector>

#include "math.h"
#include "ml.h"

int main()
{
	std::vector<double> v{1.0, 2.0, 3.0};
	std::vector<double> x{hypernex::math::scale(3, v)};
	hypernex::ml::someVectorOperation(x);

	return EXIT_SUCCESS;
}	
