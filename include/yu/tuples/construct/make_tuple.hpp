// yutool: include guard
#ifndef YU_TUPLES_CONSTRUCT_MAKE_TUPLE_HPP_
#define YU_TUPLES_CONSTRUCT_MAKE_TUPLE_HPP_

#include <yu/tuples/apply.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <tuple>
#include <utility>

namespace yu::tuples {

namespace _unspecified {

struct make_tuple_adaptor {
        template <tuple Tuple>
        [[nodiscard]]
        static constexpr decltype(auto) operator()(Tuple&& tuple) {
            return tuples::apply(
                []<typename... Elems>(Elems&&... elems) { return std::make_tuple(std::forward<Elems>(elems)...); },
                std::forward<Tuple>(tuple)
            );
        }

        template <tuple Tuple>
        [[nodiscard]]
        friend constexpr decltype(auto) operator|(Tuple&& tuple, make_tuple_adaptor) noexcept {
            return operator()(std::forward<Tuple>(tuple));
        }
};

} // namespace _unspecified

inline constexpr _unspecified::make_tuple_adaptor make_tuple{};

} // namespace yu::tuples

#endif
