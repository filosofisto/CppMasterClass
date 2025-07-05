#include "math.h"

namespace hypernex::math
{
	std::vector<double> scale(int s, const std::vector<double>& original)
	{
		std::vector result{original};

		for (auto& curr : result) {
			curr *= s;
		}

		return result;
	}
}
