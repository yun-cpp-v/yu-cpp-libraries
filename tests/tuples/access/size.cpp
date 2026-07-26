#include <yu/tuples/access/size.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>

struct std_tuple_size_defined {};

namespace std {

template <>
struct tuple_size<std_tuple_size_defined> : std::integral_constant<std::size_t, 3> {};

} // namespace std

int main() {
    using namespace yu::tuples;

    static_assert(size_v<int (&)[3]> == 3);
    static_assert(size_v<const int (&)[3]> == 3);

    static_assert(size_v<int (&&)[3]> == 3);
    static_assert(size_v<const int (&&)[3]> == 3);

    static_assert(size_v<std_tuple_size_defined> == 3);
    static_assert(size_v<const std_tuple_size_defined> == 3);

    static_assert(size_v<std_tuple_size_defined&> == 3);
    static_assert(size_v<const std_tuple_size_defined&> == 3);

    static_assert(size_v<std_tuple_size_defined&&> == 3);
    static_assert(size_v<const std_tuple_size_defined&&> == 3);
}
