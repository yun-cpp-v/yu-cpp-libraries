#include <yu/tuples/algorithm/ends_with.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(ends_with(std::tuple{1, 2, nullptr}, std::tuple{2, nullptr}));
    static_assert(ends_with(std::tuple{1, 2, 3}, std::tuple{}));
}