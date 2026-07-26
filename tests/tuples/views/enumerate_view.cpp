#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/views/enumerate_view.hpp>
#include <string_view>
#include <tuple>


int main() {
    using namespace yu::tuples;
    using namespace std::string_view_literals;

    constexpr auto v = std::tuple{"first"sv, "second"sv, "third"sv} | views::enumerate;

    static_assert(v.size == 3);
    static_assert(equal(get(v, index<0>), std::tuple{0, "first"sv}));
    static_assert(equal(get(v, index<1>), std::tuple{1, "second"sv}));
}