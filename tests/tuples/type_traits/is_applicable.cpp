#include "helpers.hpp"
#include <yu/tuples/type_traits/is_applicable.hpp>

int main() {
    using namespace yu::tuples;

    {
        using fn_t         = decltype([](double, double, double) {});
        using fn_nothrow_t = decltype([](double, double, double) noexcept {});

        static_assert(is_applicable_v<fn_t, double (&)[3]>);
        static_assert(is_nothrow_applicable_v<fn_nothrow_t, double (&)[3]>);
        static_assert(!is_nothrow_applicable_v<fn_t, double (&)[3]>);

        static_assert(!is_applicable_v<fn_t, double (&)[2]>);
        static_assert(!is_nothrow_applicable_v<fn_nothrow_t, double (&)[2]>);
        static_assert(!is_nothrow_applicable_v<fn_t, double (&)[2]>);
    }

    {
        using fn_t         = decltype([](int, void*) {});
        using fn_nothrow_t = decltype([](int, void*) noexcept {});

        static_assert(is_applicable_v<fn_t, std::tuple<int, void*>>);
        static_assert(is_nothrow_applicable_v<fn_nothrow_t, std::tuple<int, void*>>);
        static_assert(!is_nothrow_applicable_v<fn_t, std::tuple<int, void*>>);
        static_assert(!is_applicable_v<fn_t, std::tuple<int>>);
    }

    {
        using fn_t         = decltype([] {});
        using fn_nothrow_t = decltype([] noexcept {});

        static_assert(is_applicable_v<fn_t, std::tuple<>>);
        static_assert(is_nothrow_applicable_v<fn_nothrow_t, std::tuple<>>);
        static_assert(!is_applicable_v<fn_t, std::tuple<int>>);
        static_assert(!is_nothrow_applicable_v<fn_t, std::tuple<int>>);
    }

    {
        static_assert(is_applicable_r_v<long, int (*)(int, int), std::tuple<int, int>>);
        static_assert(is_nothrow_applicable_r_v<long, int (*)(int, int) noexcept, std::tuple<int, int>>);

        struct X {
                X(int) noexcept(false) {}
        };

        static_assert(!is_nothrow_applicable_r_v<X, int (*)(int, int) noexcept, std::tuple<int, int>>);

    }
}