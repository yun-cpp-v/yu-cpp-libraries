#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/views/concat_view.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto v = views::concat(std::tuple{1, 2}, std::tuple{3});

    static_assert(v.size == 3);
    static_assert(get(v, index<0>) == 1);
    static_assert(get(v, index<1>) == 2);
    static_assert(get(v, index<2>) == 3);
}