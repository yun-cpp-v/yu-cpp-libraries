#include <yu/tuples/algorithm/mismatch.hpp>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(mismatch(std::tuple{1, 2, 3, 4}, std::tuple{1, 2, 4}).value() == 2);
    static_assert(mismatch(std::tuple{1, 2, 3, 4}, std::tuple{1, 2, 3}).value() == 3);
    static_assert(mismatch(std::tuple{1, 2, 3}, std::tuple{1, 2, 3, 4}).value() == 3);
    static_assert(mismatch(std::tuple{1, 2, 3, 4}, std::tuple{1, 2, 3, 4}) == std::nullopt);
}