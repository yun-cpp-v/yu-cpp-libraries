#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/views/empty_view.hpp>
#include <yu/tuples/views/zip_view.hpp>
#include <concepts>
#include <string_view>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace std::string_view_literals;

    {
        constexpr auto v = views::zip(std::tuple{1, 2, 3}, std::tuple{"first"sv, "second"sv});

        static_assert(v.size == 2);
        static_assert(equal(get(v, index<0>), std::tuple{1, "first"sv}));
        static_assert(equal(get(v, index<1>), std::tuple{2, "second"sv}));
    }

    {
        constexpr auto v = views::zip();
        static_assert(v.size == 0);
        static_assert(std::same_as<decltype(v), const empty_view>);
    }
}