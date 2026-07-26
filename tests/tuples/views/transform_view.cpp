#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/views/transform_view.hpp>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto v = std::tuple{1, 2, 3} | views::transform([](int value) { return value + 1; });

    static_assert(std::same_as<element_type_t<0, decltype(v)>, int>);
    static_assert(get(v, index<0>) == 2);
}