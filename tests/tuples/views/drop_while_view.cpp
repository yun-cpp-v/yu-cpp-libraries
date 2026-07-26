#include <yu/meta/functions.hpp>
#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/views/drop_while_view.hpp>
#include <string_view>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace yu::meta::functions;
    using namespace std::string_view_literals;

    constexpr auto v = std::tuple{1, 2, "hello"sv, 3} | views::drop_while(integral);

    static_assert(v.size == 2);
    static_assert(get(v, index<0>) == "hello"sv);
    static_assert(get(v, index<1>) == 3);
}