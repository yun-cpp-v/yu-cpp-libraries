#include <yu/tuples/algorithm/any_of.hpp>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto pred = []<typename T>(T x) {
        if constexpr (std::integral<T>) {
            return 0 <= x;
        } else {
            return false;
        }
    };

    static_assert(any_of(std::tuple{1, "hello", -1}, pred));
    static_assert(!any_of(std::tuple{-1}, pred));
    static_assert(!any_of(std::tuple{}, pred));
}