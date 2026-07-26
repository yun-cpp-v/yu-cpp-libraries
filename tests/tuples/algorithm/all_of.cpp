#include <yu/tuples/algorithm/all_of.hpp>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    constexpr auto pred = []<typename T>(T x) {
        if constexpr (std::integral<T>) {
            return 0 <= x;
        } else {
            return true;
        }
    };

    static_assert(all_of(std::tuple{1, "hello", 3}, pred));
    static_assert(!all_of(std::tuple{1, -1}, pred));
    static_assert(all_of(std::tuple{}, pred));
}