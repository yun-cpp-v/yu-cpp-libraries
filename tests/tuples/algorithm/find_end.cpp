#include <yu/tuples/algorithm/find_end.hpp>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(find_end(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{nullptr, 2}).value() == 3);
    static_assert(find_end(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{2}).value() == 4);
    static_assert(find_end(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{}).value() == 5);
    static_assert(find_end(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{3}) == std::nullopt);
}