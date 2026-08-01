#include <yu/meta/functions.hpp>
#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/views/split_when_view.hpp>
#include <string_view>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace yu::meta::functions;
    using namespace std::string_view_literals;

    constexpr auto v = std::tuple{1, "first"sv, 2, "second"sv, 3, 4} | views::split_when(integral);

    static_assert(v.size == 3);
    static_assert(equal(get(v, index<0>), std::tuple{1}));
    static_assert(equal(get(v, index<1>), std::tuple{2}));
    static_assert(equal(get(v, index<2>), std::tuple{3, 4}));
}