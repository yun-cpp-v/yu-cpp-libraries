#include <yu/tuples/algorithm/fold_right_last.hpp>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto sub = [](auto l, auto r) { return l - r; };

    static_assert(fold_right_last(std::tuple{1, 2, 3, 4}, sub) == -2);
    static_assert(!std::invocable<decltype(fold_right_last),std::tuple<>, decltype(sub)>);
}