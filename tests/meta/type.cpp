#include <yu/meta/type.hpp>
#include <utility>

int main() {
    using namespace yu::meta;

    constexpr int value = 0;

    static_assert(type<int> == type<int>);
    static_assert(type<char> != type<int>);
    static_assert(as_type(value) == type<int>);
    static_assert(as_type(std::move(value)) == type<int>);
    static_assert(as_type(3.14) != type<int>);
}