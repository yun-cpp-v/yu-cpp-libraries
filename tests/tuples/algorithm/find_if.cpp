#include <yu/tuples/algorithm/find_if.hpp>
#include <concepts>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(find_if(std::tuple{1, nullptr, 2}, [](std::integral auto x) { return x < 2; }).value() == 0);
    static_assert(find_if(std::tuple{1, 1, nullptr, 2}, [](std::integral auto x) { return x < 2; }).value() == 0);
    static_assert(find_if(std::tuple{3, 4, 5}, [](std::integral auto x) { return x < 2; }) == std::nullopt);
    static_assert(find_if(std::tuple{}, [](auto x) { return x < 2; }) == std::nullopt);
}