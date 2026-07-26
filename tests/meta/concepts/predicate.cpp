#include <yu/meta/concepts/predicate.hpp>
#include <yu/meta/constant.hpp>
#include <yu/meta/type.hpp>

int main() {
    using namespace yu::meta;

    using pred_t = decltype([]<typename T>(type_t<T>) { return constant<true>; });

    static_assert(predicate<pred_t, type_t<int>>);
    static_assert(predicate<pred_t, const type_t<int>>);
    static_assert(predicate<pred_t, type_t<int>&>);
    static_assert(predicate<pred_t, const type_t<int>&>);
    static_assert(predicate<pred_t, type_t<int>&&>);
    static_assert(predicate<pred_t, const type_t<int>&&>);

    static_assert(!predicate<pred_t, int>);
    static_assert(!predicate<int, type_t<int>>);
    static_assert(!predicate<int, int>);
}