#include <yu/tuples/algorithm/search.hpp>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(search(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{nullptr, 2}).value() == 1);
    static_assert(search(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{2}).value() == 2);
    static_assert(search(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{}).value() == 0);
    static_assert(search(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{3}) == std::nullopt);
}