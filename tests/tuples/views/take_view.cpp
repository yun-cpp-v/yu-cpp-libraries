#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/views/take_view.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto v = std::tuple{1, 2, 3} | views::take(index<2>);

    static_assert(v.size == 2);
    static_assert(get(v, index<0>) == 1);
    static_assert(get(v, index<1>) == 2);
}