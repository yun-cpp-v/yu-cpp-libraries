#include <yu/functional/predicates.hpp>
#include <yu/tuples/algorithm/locate_last_if.hpp>
#include <concepts>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace yu::functional;

    static_assert(
        locate_last_if(std::tuple{1, nullptr, 2}, [](std::integral auto x) { return x < 2; }).value().visit([](auto x) {
            return safe_equal_to{}(x, 1);
        })
    );
    static_assert(
        locate_last_if(std::tuple{1, 1, nullptr, 2}, [](std::integral auto x) { return x < 2; }).value().index() == 1
    );
    static_assert(locate_last_if(std::tuple{3, 4, 5}, [](std::integral auto x) { return x < 2; }) == std::nullopt);
    static_assert(locate_last_if(std::tuple{}, [](auto x) { return x < 2; }) == std::nullopt);
}