#include <yu/tuples/algorithm/none_of.hpp>
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

    static_assert(none_of(std::tuple{-1, "hello", nullptr}, pred));
    static_assert(!none_of(std::tuple{10}, pred));
    static_assert(none_of(std::tuple{}, pred));
}