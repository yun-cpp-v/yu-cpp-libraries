#include <yu/tuples/algorithm/count_if.hpp>
#include <tuple>

int main() {
    using namespace yu::tuples;

    static_assert(count_if(std::tuple{1, 2, 2, nullptr}, [](std::integral auto x) { return x <= 2; }) == 3);
    static_assert(count_if(std::tuple{1, 2, 2, nullptr}, [](auto) { return false; }) == 0);
}