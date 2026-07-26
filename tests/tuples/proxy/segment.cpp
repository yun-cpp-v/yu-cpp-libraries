#include <yu/functional/predicates.hpp>
#include <yu/tuples/proxy/segment.hpp>
#include <ranges>
#include <string_view>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace yu::functional;
    using namespace std::string_view_literals;

    {
        constexpr auto seg = segment{std::tuple{1, "hello"sv, 2, nullptr}, 1, 2};
        using seg_t        = decltype(seg);

        static_assert(std::ranges::random_access_range<seg_t>);
        static_assert(seg.size() == 2);

        constexpr bool test = [&] {
            if (!seg[0].visit([](auto x) { return safe_equal_to{}(x, "hello"sv); })) return false;
            if (!seg[1].visit([](auto x) { return safe_equal_to{}(x, 2); })) return false;
            return true;
        }();

        static_assert(test);
    }
}