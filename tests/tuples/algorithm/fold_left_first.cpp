#include <yu/tuples/algorithm/fold_left_first.hpp>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto sub = [](auto l, auto r) { return l - r; };

    static_assert(fold_left_first(std::tuple{1, 2, 3, 4}, sub) == -8);
    static_assert(!std::invocable<decltype(fold_left_first),std::tuple<>, decltype(sub)>);
}