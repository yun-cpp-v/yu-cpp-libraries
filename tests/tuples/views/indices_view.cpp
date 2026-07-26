#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/views/indices_view.hpp>


int main() {
    using namespace yu::tuples;

    constexpr auto v = views::indices(index<3>);

    static_assert(v.size == 3);
    static_assert(get(v, index<0>) == index<0>);
    static_assert(get(v, index<1>) == index<1>);
}