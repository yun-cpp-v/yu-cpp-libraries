#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/views/as_rvalue_view.hpp>
#include <tuple>
#include <type_traits>

int main() {
    using namespace yu::tuples;

    constexpr auto v = std::tuple{1, 2, 3} | views::as_rvalue;

    static_assert(std::is_rvalue_reference_v<element_type_t<0, decltype(v)>>);
    static_assert(std::same_as<element_type_t<0, decltype(v)>, const int&&>);
    static_assert(get(v, index<1>) == 2);
}