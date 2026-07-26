#include <yu/tuples/algorithm/contains_subtuple.hpp>
#include <string_view>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace std::string_view_literals;

    static_assert(contains_subtuple(std::tuple{1, 2, "hello"sv, 4}, std::tuple{1, 2}));
    static_assert(!contains_subtuple(std::tuple{1, 2, "hello"sv, 4}, std::tuple{1, 4}));
    static_assert(contains_subtuple(std::tuple{1, 2, "hello"sv, 4}, std::tuple{"hello"sv, 4}));
    static_assert(contains_subtuple(std::tuple{1, 2, "hello"sv, 4}, std::tuple{}));
}