#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/views/reverse_view.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto v = std::tuple{1, 2, 3} | views::reverse;

    static_assert(v.size == 3);
    static_assert(get(v, index<0>) == 3);
    static_assert(get(v, index<1>) == 2);
}