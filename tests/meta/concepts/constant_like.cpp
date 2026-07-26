#include <yu/meta/concepts/constant_like.hpp>
#include <yu/meta/constant.hpp>
#include <cstddef>
#include <type_traits>

int main() {
    using namespace yu::meta;

    static_assert(constant_like<constant_t<1>>);
    static_assert(constant_like<std::integral_constant<int, 1>>);

    static_assert(constant_like_of<constant_t<1>, int>);
    static_assert(constant_like_of<constant_t<nullptr>, std::nullptr_t>);
    static_assert(constant_like_of<std::integral_constant<int, 1>, int>);

    static_assert(!constant_like<int>);
    static_assert(!constant_like_of<int, char>);
}