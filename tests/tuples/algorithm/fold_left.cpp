#include <yu/tuples/algorithm/fold_left.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto sub = [](auto l, auto r) { return l - r; };

    static_assert(fold_left(std::tuple{2, 3, 4}, 1, sub) == -8);
    static_assert(fold_left(std::tuple{}, 1, sub) == 1);
}