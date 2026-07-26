#include <yu/functional/predicates.hpp>
#include <yu/tuples/algorithm/match.hpp>
#include <optional>
#include <tuple>

int main() {
    using namespace yu::tuples;
    using namespace yu::functional;
    {
        constexpr bool test = [] {
            auto seg_opt = match(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{nullptr, 2});

            if (!seg_opt.has_value()) return false;

            auto seg = seg_opt.value();

            if (seg.size() != 2) return false;

            if (seg[0].index() != 1) return false;
            if (seg[1].index() != 2) return false;

            if (!seg[0].visit([](auto x) { return safe_equal_to{}(x, nullptr); })) return false;
            if (!seg[1].visit([](auto x) { return safe_equal_to{}(x, 2); })) return false;

            return true;
        }();

        static_assert(test);
    }

    static_assert(match(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{}).value().size() == 0);
    static_assert(match(std::tuple{1, nullptr, 2, nullptr, 2}, std::tuple{3}) == std::nullopt);
}