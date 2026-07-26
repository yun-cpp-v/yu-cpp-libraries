#include <yu/tuples/type_traits/is_gettable.hpp>
#include <yu/tuples/views/empty_view.hpp>

int main() {
    using namespace yu::tuples;

    static_assert(views::empty.size == 0);
    static_assert(!is_gettable_v<0, decltype(views::empty)>);
}