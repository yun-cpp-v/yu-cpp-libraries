#include <yu/tuples/algorithm/search_n.hpp>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(search_n(std::tuple{1, nullptr, nullptr, nullptr, 2}, nullptr, index<2>).value() == 1);
    static_assert(search_n(std::tuple{1, nullptr, nullptr, nullptr, 2}, nullptr, index<3>).value() == 1);
    static_assert(search_n(std::tuple{1, nullptr, 2, nullptr, 2}, 3, index<1>) == std::nullopt);
    static_assert(search_n(std::tuple{1, nullptr, 2, nullptr, 2}, 3, index<0>).value() == 0);
    static_assert(search_n(std::tuple{}, 3, index<0>).value() == 0);
}