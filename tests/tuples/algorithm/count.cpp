#include <yu/tuples/algorithm/count.hpp>
#include <string_view>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace std::string_view_literals;

    static_assert(count(std::tuple{1, 2, 2, nullptr}, 2) == 2);
    static_assert(count(std::tuple{1, 2, 2, nullptr}, "hello"sv) == 0);
}