#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/access/size.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/views/cartesian_product_view.hpp>
#include <yu/tuples/views/single_view.hpp>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    {
        constexpr auto v = views::cartesian_product(std::tuple{1, 2}, std::tuple{'a', 'b', 'c'});

        static_assert(v.size == 6);
        static_assert(equal(get(v, index<0>), std::tuple{1, 'a'}));
        static_assert(equal(get(v, index<3>), std::tuple{2, 'a'}));
        static_assert(equal(get(v, index<5>), std::tuple{2, 'c'}));
    }

    {
        constexpr auto v = views::cartesian_product();

        static_assert(v.size == 1);
        static_assert(std::same_as<decltype(v), const single_view<std::tuple<>>>);
    }
}