#include <yu/meta/functions/concepts/integral.hpp>
#include <yu/tuples/concepts/elementwise_meta_predicate.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace yu::meta::functions;

    static_assert(elementwise_meta_predicate<decltype(integral), std::tuple<int, void*>>);
    static_assert(elementwise_meta_predicate<decltype(integral), std::tuple<>>);
    static_assert(!elementwise_meta_predicate<int, std::tuple<int, void*>>);
    static_assert(elementwise_meta_predicate<int, std::tuple<>>);
}