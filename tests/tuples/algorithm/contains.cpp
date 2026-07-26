#include <yu/tuples/algorithm/contains.hpp>
#include <tuple>
#include <string_view>

int main() {
    using namespace yu::tuples;
    constexpr auto sv = std::string_view{"hello"};

    static_assert(contains(std::tuple{1, sv, -1}, 1));
    static_assert(!contains(std::tuple{1, 1 -1}, 10));
    static_assert(!contains(std::tuple{}, 10));
}