#include <yu/tuples/algorithm/find_last.hpp>
#include <tuple>
#include <optional>

int main(){
    using namespace yu::tuples;

    static_assert(find_last(std::tuple{1, nullptr, 2}, 2).value() == 2);
    static_assert(find_last(std::tuple{1, nullptr, 2, 2}, 2).value() == 3);
    static_assert(find_last(std::tuple{1, nullptr, 2}, 5) == std::nullopt);

}