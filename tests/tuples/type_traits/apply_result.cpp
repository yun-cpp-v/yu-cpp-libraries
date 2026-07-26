#include "helpers.hpp"
#include <yu/tuples/type_traits/apply_result.hpp>
#include <concepts>
#include <tuple>

struct overloads_t {
        int    operator()(int, void*);
        double operator()(int, int);
};

int main() {
    using namespace yu::tuples;

    static_assert(std::same_as<apply_result_t<overloads_t, std::tuple<int, void*>>, int>);
    static_assert(std::same_as<apply_result_t<overloads_t, std::tuple<int, int>>, double>);
    static_assert(std::same_as<apply_result_t<overloads_t, int (&)[2]>, double>);
    static_assert(std::same_as<apply_result_t<char (*)(int, void*), std::tuple<int, void*>>, char>);

    static_assert(!member_type_defined<apply_result<overloads_t, std::tuple<int>>>);
    static_assert(!member_type_defined<apply_result<overloads_t, std::tuple<double*, void*>>>);

    static_assert(!member_type_defined<apply_result<int, std::tuple<>>>);
}