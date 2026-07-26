#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/views/owning_view.hpp>
#include <tuple>
#include <utility>

template <typename T>
concept owning_viewable = requires(T&& t) { yu::tuples::owning_view{std::forward<T>(t)}; };

int main() {
    using namespace yu::tuples;

    {
        constexpr bool test = [] {
            auto tup = std::tuple{1, 2, 3};

            auto rv = owning_view{std::move(tup)};

            if (!equal(rv, tup)) return false;

            get(tup, index<0>) = 2;
            if (get(rv, index<0>) != 1) return false;

            get(rv, index<1>) = 4;
            if (get(tup, index<1>) != 2) return false;

            return true;
        }();

        static_assert(test);
    }

    static_assert(!owning_viewable<std::tuple<int>&>);
    static_assert(!owning_viewable<const std::tuple<int>&>);
    static_assert(owning_viewable<std::tuple<int>&&>);
    static_assert(!owning_viewable<const std::tuple<int>&&>);
    static_assert(!owning_viewable<int>);
}