#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/algorithm/equal.hpp>
#include <yu/tuples/views/ref_view.hpp>
#include <tuple>
#include <utility>

template <typename T>
concept ref_viewable = requires(T&& t) { yu::tuples::ref_view{std::forward<T>(t)}; };

int main() {
    using namespace yu::tuples;

    {
        constexpr bool test = [] {
            auto tup = std::tuple{1, 2, 3};

            auto rv = ref_view{tup};

            if (!equal(rv, tup)) return false;

            get(tup, index<0>) = 2;
            if (get(rv, index<0>) != 2) return false;

            get(rv, index<1>) = 4;
            if (get(tup, index<1>) != 4) return false;

            return true;
        }();

        static_assert(test);
    }

    static_assert(ref_viewable<std::tuple<int>&>);
    static_assert(ref_viewable<const std::tuple<int>&>);
    static_assert(!ref_viewable<std::tuple<int>>);
    static_assert(!ref_viewable<std::tuple<int>&&>);
    static_assert(!ref_viewable<int>);
}