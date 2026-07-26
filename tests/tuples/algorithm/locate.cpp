#include <yu/functional/predicates.hpp>
#include <yu/tuples/algorithm/locate.hpp>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace yu::functional;

    static_assert(locate(std::tuple{1, nullptr, 2}, 2).value().visit([](auto x) { return safe_equal_to{}(x, 2); }));
    static_assert(locate(std::tuple{1, nullptr, 2, 2}, 2).value().index() == 2);
    static_assert(locate(std::tuple{1, nullptr, 2}, 5) == std::nullopt);
}
