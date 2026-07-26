#include <yu/tuples/concepts/elementwise_unary_predicate.hpp>
#include <tuple>
#include <type_traits>

int main() {
    using namespace yu::tuples;

    {
        using fn_t = decltype([](int) -> bool { return true; });
        static_assert(elementwise_unary_predicate<fn_t, int (&)[3]>);
        static_assert(elementwise_unary_predicate<fn_t, std::tuple<int, short>>);
        static_assert(elementwise_unary_predicate<fn_t, std::tuple<>>);
        static_assert(!elementwise_unary_predicate<fn_t, char*(&)[3]>);
    }

    static_assert(elementwise_unary_predicate<bool (*)(int), int (&)[2]>);
    static_assert(elementwise_unary_predicate<std::add_pointer_t<void*> (*)(int), int (&)[2]>);
}