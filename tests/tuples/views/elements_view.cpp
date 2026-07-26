#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/views/elements_view.hpp>
#include <string_view>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace std::string_view_literals;

    constexpr auto v = views::elements(
        std::tuple{
            std::tuple{1, 2, 3},
            std::tuple{"first"sv, "second"sv}
    },
        index<0>
    );

    static_assert(v.size == 2);
    static_assert(get(v, index<0>) == 1);
    static_assert(get(v, index<1>) == "first"sv);
}