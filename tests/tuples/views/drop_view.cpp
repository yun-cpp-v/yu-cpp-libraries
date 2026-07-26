#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/views/drop_view.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto v = std::tuple{1, 2, 3} | views::drop(index<1>);

    static_assert(v.size == 2);
    static_assert(get(v, index<0>) == 2);
    static_assert(get(v, index<1>) == 3);
}