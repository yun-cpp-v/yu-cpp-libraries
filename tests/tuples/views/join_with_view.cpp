#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/views/join_with_view.hpp>
#include <string_view>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace std::string_view_literals;

    {
        constexpr auto v = std::tuple{std::tuple{1, 2, 3}, std::tuple{"first"sv, "second"sv}} | views::join_with(std::tuple{271, 314});

        static_assert(v.size == 7);
        static_assert(equal(v, std::tuple{1, 2, 3, 271, 314, "first"sv, "second"sv}));
    }
}