#include <yu/tuples/construct/make_tuple.hpp>
#include <array>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(std::same_as<decltype(make_tuple(std::array<int, 3>{})), std::tuple<int, int, int>>);
    static_assert(std::same_as<decltype(std::array<int, 3>{} | make_tuple), std::tuple<int, int, int>>);
    static_assert(std::same_as<decltype(std::array<const int, 3>{} | make_tuple), std::tuple<int, int, int>>);
}
