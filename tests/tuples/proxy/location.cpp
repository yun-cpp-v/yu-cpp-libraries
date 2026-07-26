#include <yu/functional/predicates.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/proxy/location.hpp>
#include <concepts>
#include <string_view>
#include <tuple>
#include <type_traits>

int main() {
    using namespace yu::tuples;
    using namespace yu::functional;
    using namespace std::string_view_literals;

    static constexpr auto tup = std::tuple{1, "hello"sv, 3};

    constexpr auto loc1 = location{tup, 0};
    constexpr auto loc2 = location{tup, 1};

    static_assert(std::same_as<decltype(loc1), decltype(loc2)>);

    {
        static_assert(loc1.index() == 0);
        static_assert(equal(loc1.base(), tup));
        static_assert(loc1.visit([](auto x) { return safe_equal_to{}(x, 1); }));
        static_assert(!loc1.visit([](auto x) { return safe_equal_to{}(x, "hello"sv); }));
    }
    {
        static_assert(loc2.index() == 1);
        static_assert(equal(loc2.base(), tup));
        static_assert(loc2.visit([](auto x) { return safe_equal_to{}(x, "hello"sv); }));
        static_assert(!loc2.visit([](auto x) { return safe_equal_to{}(x, 3); }));
    }

    {
        constexpr bool test = [] {
            auto tup = std::tuple{1, "hello"sv, 3};
            auto loc = location{tup, 0};

            loc.visit([](auto& x) {
                if constexpr (std::same_as<std::decay_t<decltype(x)>, int>) x = 2;
            });

            return get(tup, index<0>) == 2;
        }();

        static_assert(test);
    }

    { static_assert(std::is_empty_v<decltype(location{std::tuple{}, 0})>); }
}