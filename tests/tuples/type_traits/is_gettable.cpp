#include <yu/tuples/type_traits/is_gettable.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>

struct throw_get_t {
        template <std::size_t>
        int get() noexcept(false);
};

namespace std {

template <>
struct tuple_size<throw_get_t> : std::integral_constant<std::size_t, 2> {};

} // namespace std

int main() {
    using namespace yu::tuples;

    static_assert(is_gettable_v<0, std::tuple<void*, int>>);
    static_assert(is_gettable_v<0, const std::tuple<void*, int>>);
    static_assert(is_gettable_v<0, std::tuple<void*, int>&>);
    static_assert(is_gettable_v<0, const std::tuple<void*, int>&>);
    static_assert(is_gettable_v<0, std::tuple<void*, int>&&>);
    static_assert(is_gettable_v<0, const std::tuple<void*, int>&&>);

    static_assert(is_gettable_v<0, int (&)[3]>);
    static_assert(is_gettable_v<0, const int (&)[3]>);
    static_assert(is_gettable_v<0, int (&&)[3]>);
    static_assert(is_gettable_v<0, const int (&&)[3]>);

    static_assert(!is_gettable_v<2, std::tuple<void*, int>>);
    static_assert(!is_gettable_v<3, int (&)[3]>);

    static_assert(is_nothrow_gettable_v<0, std::tuple<void*, int>>);
    static_assert(is_nothrow_gettable_v<0, int (&)[3]>);

    static_assert(!is_nothrow_gettable_v<2, std::tuple<void*, int>>);
    static_assert(!is_nothrow_gettable_v<3, int (&)[3]>);

    static_assert(!is_nothrow_gettable_v<0, throw_get_t>);
}