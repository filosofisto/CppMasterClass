#include <iostream>
#include "math.h"
#include "ml.h"

namespace hypernex::ml
{
	void someVectorOperation(const std::vector<double>& v)
	{
		auto newVector = hypernex::math::scale(5, v);
		std::cout << "Some vector operation\n";
	}
}
