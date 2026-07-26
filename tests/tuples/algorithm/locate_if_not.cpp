#include <yu/functional/predicates.hpp>
#include <yu/tuples/algorithm/locate_if_not.hpp>
#include <concepts>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace yu::functional;

    static_assert(locate_if_not(std::tuple{1, 1, nullptr, 3}, [](std::integral auto x) { return 2 < x; })
                      .value()
                      .visit([](auto x) { return safe_equal_to{}(x, 1); }));
    static_assert(locate_if_not(std::tuple{3, 4, 5}, [](std::integral auto x) { return 2 < x; }) == std::nullopt);
    static_assert(locate_if_not(std::tuple{}, [](auto x) { return 2 < x; }) == std::nullopt);
}