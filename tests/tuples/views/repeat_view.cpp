#include <yu/tuples/type_traits/is_gettable.hpp>
#include <yu/tuples/views/repeat_view.hpp>

int main() {
    using namespace yu::tuples;

    constexpr auto v = views::repeat(1, index<3>);

    static_assert(v.size == 3);
    static_assert(get(v, index<0>) == 1);
}