#include <yu/tuples/concepts/tuple.hpp>
#include <tuple>

struct zero_size_no_get {};

namespace std {

template <>
struct tuple_size<zero_size_no_get> : std::integral_constant<std::size_t, 0> {};

} // namespace std

int main() {
    using namespace yu::tuples;

    static_assert(tuple<int[3]>);
    static_assert(tuple<const int[3]>);

    static_assert(tuple<int (&)[3]>);
    static_assert(tuple<const int (&)[3]>);

    static_assert(tuple<int (&&)[3]>);
    static_assert(tuple<const int (&&)[3]>);

    static_assert(tuple<std::tuple<int, bool>>);
    static_assert(tuple<const std::tuple<int, bool>>);

    static_assert(tuple<std::tuple<int, bool>&>);
    static_assert(tuple<const std::tuple<int, bool>&>);

    static_assert(tuple<std::tuple<int, bool>&&>);
    static_assert(tuple<const std::tuple<int, bool>&&>);

    static_assert(tuple<zero_size_no_get>);

    static_assert(!tuple<int>);
}