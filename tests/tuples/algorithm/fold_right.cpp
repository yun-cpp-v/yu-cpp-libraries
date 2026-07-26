#include <yu/tuples/algorithm/fold_right.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto sub = [](auto l, auto r) { return l - r; };

    static_assert(fold_right(std::tuple{2, 3, 4}, 1, sub) == -2);
    static_assert(fold_right(std::tuple{}, 1, sub) == 1);
}