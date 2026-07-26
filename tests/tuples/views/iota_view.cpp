#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/views/iota_view.hpp>


int main() {
    using namespace yu::tuples;

    constexpr auto v = views::iota(index<5>, index<10>);

    static_assert(v.size == 5);
    static_assert(get(v, index<0>) == 5);
    static_assert(get(v, index<4>) == 9);
}