#include <yu/tuples/concepts/constructible_from_elements.hpp>
#include <tuple>

template <typename... Ts>
struct X {
        explicit X(Ts...) {}
};

int main() {
    using namespace yu::tuples;

    static_assert(constructible_from_elements<X<int, int, int>, int (&)[3]>);
    static_assert(constructible_from_elements<X<int, int, int>, int (&)[2], int>);
    static_assert(constructible_from_elements<X<int, bool, char*>, std::tuple<int, bool, char*>>);
    static_assert(constructible_from_elements<X<int, bool, char*>, std::tuple<int, bool>, char*>);
    static_assert(constructible_from_elements<X<>, std::tuple<>>);
    static_assert(!constructible_from_elements<X<int, char*>, std::tuple<int, bool, char*>>);
}