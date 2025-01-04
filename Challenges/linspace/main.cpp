#include <iostream>
#include <array>
#include <concepts>
#include <type_traits>
#include <stdexcept>

using std::array, std::cout, std::endl, std::is_arithmetic_v, std::runtime_error, std::cerr;

template<typename T>
concept Arithmetic = is_arithmetic_v<T>;

template<Arithmetic T, size_t N>
array<double, N> linspace(T start, T end, bool endpoint)
{
    static_assert(N > 0, "Array size must to have at least one item");

    if (start >= end) {
        throw runtime_error("End have to be greater than start");
    }

    array<double, N> ret = {};
    double dstart = static_cast<double>(start);
    double dend = static_cast<double>(end); 
    ret[0] = dstart;
    
    if (endpoint) {    
        ret[N-1] = dend;
        double delta{ (dend-dstart)/(N-1) };

        for (size_t i{1}; i < N-1; ++i) {
            ret[i] = ret[i-1] + delta;
        }
    } else {
        double delta{ (dend-dstart)/N };    
    
        for (size_t i{1}; i < N; ++i) {
            ret[i] = ret[i-1] + delta;
        }
    }
    
    return ret;
}

template<size_t N>
void show(const array<double, N> values)
{
    for (const auto& item: values) {
        cout << item << " ";
    }

    cout << endl;
}

int main()
{
    try {
        auto arrayA1 = linspace<int, 4>(0, 6, true);
        show(arrayA1);

        auto arrayA2 = linspace<int, 4>(0, 6, false);
        show(arrayA2);

        auto arrayB1 = linspace<int, 10>(0, 4, true);
        show(arrayB1);

        auto arrayB2 = linspace<int, 10>(0, 4, false);
        show(arrayB2);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
