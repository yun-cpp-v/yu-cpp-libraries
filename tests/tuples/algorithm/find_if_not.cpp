#include <yu/tuples/algorithm/find_if_not.hpp>
#include <concepts>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(find_if_not(std::tuple{1, 1, nullptr, 3}, [](std::integral auto x) { return 2 < x; }).value() == 0);
    static_assert(find_if_not(std::tuple{3, 4, 5}, [](std::integral auto x) { return 2 < x; }) == std::nullopt);
    static_assert(find_if_not(std::tuple{}, [](auto x) { return 2 < x; }) == std::nullopt);
}