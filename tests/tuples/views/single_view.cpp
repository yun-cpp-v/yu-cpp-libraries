#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/type_traits/is_gettable.hpp>
#include <yu/tuples/views/single_view.hpp>

int main() {
    using namespace yu::tuples;

    constexpr auto v = views::single(1);

    static_assert(v.size == 1);
    static_assert(get(v, index<0>) == 1);
}