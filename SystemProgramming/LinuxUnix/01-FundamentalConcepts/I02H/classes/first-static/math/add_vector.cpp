#include "hypernex_math.h"

namespace hypernex
{
	/**
	 * a = a + b
	 */
	void add_vector(std::vector<int>& a, const std::vector<int>& b)
	{
		if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be of the same size.");
    }

    for (size_t i{0}; i < a.size(); ++i) {
        a[i] += b[i];
    }
	}
}
