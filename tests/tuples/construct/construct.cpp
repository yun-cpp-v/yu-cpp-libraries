#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/construct/construct.hpp>
#include <yu/tuples/views/all.hpp>
#include <array>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(
        std::same_as<decltype(construct<std::tuple>(std::array<int, 3>{}, 0)), std::tuple<int, int, int, int>>
    );
    static_assert(
        std::same_as<decltype(std::array<int, 3>{} | construct<std::tuple>(0)), std::tuple<int, int, int, int>>
    );
}