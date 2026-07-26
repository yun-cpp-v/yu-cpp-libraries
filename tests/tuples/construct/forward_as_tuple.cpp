#include <yu/tuples/construct/forward_as_tuple.hpp>
#include <array>
#include <concepts>
#include <tuple>
#include <utility>

int main() {
    using namespace yu::tuples;

    constexpr auto arr = std::array<int, 3>{};

    static_assert(std::same_as<decltype(forward_as_tuple(arr)), std::tuple<const int&, const int&, const int&>>);
    static_assert(std::same_as<decltype(arr | forward_as_tuple), std::tuple<const int&, const int&, const int&>>);
    static_assert(
        std::same_as<decltype(forward_as_tuple(std::move(arr))), std::tuple<const int&&, const int&&, const int&&>>
    );
    static_assert(
        std::same_as<decltype(std::move(arr) | forward_as_tuple), std::tuple<const int&&, const int&&, const int&&>>
    );
}