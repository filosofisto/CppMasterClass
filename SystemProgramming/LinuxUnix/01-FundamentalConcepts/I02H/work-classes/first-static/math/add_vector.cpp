#include "hypernex_math.h"
#include <stdexcept>

namespace hypernex
{
	void add_vector(std::vector<int>& a, const std::vector<int>& b)
	{
		if (a.size() != b.size()) {
			throw std::invalid_argument("Vectors need to have equal size");
		}

		for (size_t i{0}; i < a.size(); ++i) {
			a[i] += b[i];
		}
	}
}
