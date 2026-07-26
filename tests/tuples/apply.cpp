#include <yu/tuples/apply.hpp>

int main() {
    using namespace yu::tuples;

    {
        constexpr int arr[3] = {1, 2, 3};

        static_assert(apply([](int a, int b, int c) { return a + b + c; }, arr) == 6);
    }

    {
        constexpr std::tuple<int, double, char> tup{1, 3.14, 'c'};

        static_assert(apply([](auto a, auto b, auto c) { return (a == 1) && (b == 3.14) && (c == 'c'); }, tup));
    }
}