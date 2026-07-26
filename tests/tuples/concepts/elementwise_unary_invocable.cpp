#include <yu/tuples/concepts/elementwise_unary_invocable.hpp>
#include <tuple>

struct overloads_t {
        void operator()(int) {}

        void operator()(float) {}

        void operator()(void*) {}
};

int main() {
    using namespace yu::tuples;

    static_assert(elementwise_unary_invocable<overloads_t, std::tuple<int, float, void*>>);
    static_assert(elementwise_unary_invocable<overloads_t, int (&)[3]>);
    static_assert(elementwise_unary_invocable<int, std::tuple<>>);
}