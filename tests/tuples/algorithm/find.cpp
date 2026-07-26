#include <yu/tuples/algorithm/find.hpp>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(find(std::tuple{1, nullptr, 2}, 2).value() == 2);
    static_assert(find(std::tuple{1, nullptr, 2, 2}, 2).value() == 2);
    static_assert(find(std::tuple{1, nullptr, 2}, 5) == std::nullopt);
}
