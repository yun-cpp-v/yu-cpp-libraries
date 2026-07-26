#include <yu/tuples/algorithm/starts_with.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(starts_with(std::tuple{1, 2, nullptr}, std::tuple{1, 2}));
    static_assert(starts_with(std::tuple{1, 2, 3}, std::tuple{}));
}