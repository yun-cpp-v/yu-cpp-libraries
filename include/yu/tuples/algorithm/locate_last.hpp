// yutool: include guard
#ifndef YU_TUPLES_ALGORITHM_LOCATE_LAST_HPP_
#define YU_TUPLES_ALGORITHM_LOCATE_LAST_HPP_

#include "find_last.hpp"
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/projected.hpp>
#include <yu/tuples/proxy/location.hpp>
#include <functional>
#include <utility>

namespace yu::tuples {

namespace _unspecified {

struct locate_last_fn {
        template <tuple Tuple, typename T, typename Proj = std::identity>
        [[nodiscard]]
        static constexpr decltype(auto) operator()(Tuple&& tuple, const T& value, Proj proj = {}) {
            auto&& result = find_last(std::forward<Tuple>(tuple), value, std::ref(proj));

            return result.transform([&](std::size_t index) { return location{std::forward<Tuple>(tuple), index}; });
        }
};

} // namespace _unspecified

inline namespace _fn {

inline constexpr _unspecified::locate_last_fn locate_last{};

}

} // namespace yu::tuples

#endif
