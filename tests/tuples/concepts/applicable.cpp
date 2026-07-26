#include <yu/tuples/concepts/applicable.hpp>

int main() {
    using namespace yu::tuples;

    {
        using fn_t = decltype([](double, double, double) {});

        static_assert(applicable<fn_t, double (&)[3]>);
        static_assert(!applicable<fn_t, double (&)[2]>);
    }

    {
        using fn_t = decltype([](int, double) {});

        static_assert(applicable<fn_t, std::tuple<int, double>>);
        static_assert(!applicable<fn_t, std::tuple<int>>);
    }

    {
        using fn_t = decltype([] {});

        static_assert(applicable<fn_t, std::tuple<>>);
        static_assert(!applicable<fn_t, std::tuple<int>>);
    }
}