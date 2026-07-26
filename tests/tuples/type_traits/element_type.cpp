#include "helpers.hpp"
#include <yu/tuples/type_traits/element_type.hpp>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(std::same_as<element_type_t<0, std::tuple<int, void*>>, int&&>);
    static_assert(std::same_as<element_type_t<0, std::tuple<int, void*>&>, int&>);
    static_assert(std::same_as<element_type_t<0, std::tuple<int, void*>&&>, int&&>);

    static_assert(std::same_as<element_type_t<0, const std::tuple<int, void*>>, const int&&>);
    static_assert(std::same_as<element_type_t<0, const std::tuple<int, void*>&>, const int&>);
    static_assert(std::same_as<element_type_t<0, const std::tuple<int, void*>&&>, const int&&>);

    static_assert(std::same_as<element_type_t<1, std::tuple<int, void*>>, void*&&>);
    static_assert(std::same_as<element_type_t<1, std::tuple<int, void*>&>, void*&>);
    static_assert(std::same_as<element_type_t<1, std::tuple<int, void*>&&>, void*&&>);

    static_assert(std::same_as<element_type_t<0, int (&)[3]>, int&>);
    static_assert(std::same_as<element_type_t<0, int (&&)[3]>, int&&>);

    static_assert(std::same_as<element_type_t<0, const int (&)[3]>, const int&>);
    static_assert(std::same_as<element_type_t<0, const int (&&)[3]>, const int&&>);

    static_assert(!member_type_defined<element_type<0, std::tuple<>>>);
}