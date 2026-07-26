#include <yu/tuples/access/index.hpp>
#include <yu/tuples/algorithm/for_each_n.hpp>
#include <tuple>


int main() {
    using namespace yu::tuples;

    {
        constexpr int result = [] {
            int result = 1;
            for_each_n(std::tuple{1, 2, 3, 4}, index<3>, [&](auto x) { result += x; });

            return result;
        }();
        static_assert(result == 7);
    }

    {
        constexpr bool is_called = [] {
            bool result = false;

            for_each_n(std::tuple{1, 2}, index<0>, [&](auto) { result = true; });

            return result;
        }();

        static_assert(is_called == false);
    }
}