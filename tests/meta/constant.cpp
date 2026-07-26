#include <yu/meta/constant.hpp>
#include <concepts>
#include <cstdint>
#include <type_traits>

int main() {
    using namespace yu::meta;

    {
        constexpr auto plus      = [](int a, int b) { return a + b; };
        constexpr auto plus_cnst = constant<plus>;

        static_assert(plus_cnst(constant<1>, constant<2>) == constant<3>);
    }

    {
        static constexpr int arr[]    = {1, 2};
        constexpr auto       arr_cnst = constant<arr>;

        static_assert(arr_cnst[constant<0>] == constant<1>);
    }

    {
        static_assert(+constant<1> == constant<1>);
        static_assert(-constant<1> == constant<-1>);

        constexpr int8_t a = 0b00001111, b = 0b11110000;
        static_assert(~constant<a> == constant<b>);

        static_assert(!constant<false> == constant<true>);
    }

    {
        static_assert(constant<3> + constant<2> == constant<5>);
        static_assert(constant<3> - constant<2> == constant<1>);
        static_assert(constant<3> * constant<2> == constant<6>);
        static_assert(constant<2> / constant<2> == constant<1>);
        static_assert(constant<3> % constant<2> == constant<1>);
    }

    {
        static_assert(constant<1> < constant<2>);
        static_assert(constant<1> <= constant<2>);
        static_assert(constant<2> > constant<1>);
        static_assert(constant<2> >= constant<1>);

        static_assert(constant<2> != constant<1>);
    }

    {
        static_assert(constant<true> && constant<false> == constant<false>);
        static_assert(constant<true> || constant<false> == constant<true>);
    }

    {
        using type = constant_t<1>;
        static_assert(std::same_as<type::type, type>);
        static_assert(std::same_as<type::value_type, int>);
        static_assert(std::same_as<type::integral_constant, std::integral_constant<int, 1>>);

        static_assert(std::is_default_constructible_v<type>);

        static_assert(constant_t{std::integral_constant<int, 1>{}} == constant<1>);

        static_assert(std::convertible_to<type, int>);
    }

    {
        struct X {
                int i;
        };

        constexpr X x{0};

        static_assert(constant_invoke(constant<[] { return true; }>) == constant<true>);
        static_assert(constant_invoke(constant<&X::i>, constant<x>) == constant<0>);
    }
}