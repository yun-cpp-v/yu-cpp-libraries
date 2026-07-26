#include <yu/tuples/algorithm/equal.hpp>

int main() {
    using namespace yu::tuples;

    static_assert(equal(std::tuple{1, nullptr, 3}, std::tuple{1, nullptr, 3}));
    static_assert(equal(std::tuple{}, std::tuple{}));
}