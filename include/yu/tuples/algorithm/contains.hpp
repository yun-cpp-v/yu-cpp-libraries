// yutool: include guard
#ifndef YU_TUPLES_ALGORITHM_CONTAINS_HPP_
#define YU_TUPLES_ALGORITHM_CONTAINS_HPP_

#include "any_of.hpp"
#include "yu/functional/predicates.hpp"
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/projected.hpp>
#include <functional>
#include <utility>

namespace yu::tuples {

namespace _unspecified {

struct contains_fn {
    public:
        template <tuple Tuple, typename T, typename Proj = std::identity>
        [[nodiscard]]
        static constexpr bool operator()(Tuple&& tuple, const T& value, Proj proj = {}) {
            return tuples::any_of(
                std::forward<Tuple>(tuple),
                std::bind_back(functional::safe_equal_to{}, value),
                std::ref(proj)
            );
        }
};

} // namespace _unspecified

inline namespace _fn {

inline constexpr _unspecified::contains_fn contains{};

}

} // namespace yu::tuples

#endif
