#include <yu/tuples/algorithm/find_first_of.hpp>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(find_first_of(std::tuple{1, 2, 3}, std::tuple{1}).value() == 0);
    static_assert(find_first_of(std::tuple{1, 2, 3}, std::tuple{2.0}).value() == 1);
    static_assert(find_first_of(std::tuple{1, 2, 3}, std::tuple{nullptr}) == std::nullopt);
    static_assert(find_first_of(std::tuple{1, 2, 3}, std::tuple{}) == std::nullopt);
}