// yutool: include guard
#ifndef YU_TUPLES_ALGORITHM_DETAIL_FOLD_RIGHT_IMPL_HPP_
#define YU_TUPLES_ALGORITHM_DETAIL_FOLD_RIGHT_IMPL_HPP_

#include <functional>
#include <utility>

namespace yu::tuples::_detail {

template <typename F, typename RevHead, typename RevNext, typename... RevTail>
constexpr decltype(auto) fold_right_impl(F& f, RevHead&& rev_head, RevNext&& rev_next, RevTail&&... rev_tail) {
    if constexpr (sizeof...(RevTail) == 0) {
        return std::invoke(f, std::forward<RevNext>(rev_next), std::forward<RevHead>(rev_head));
    } else {
        return fold_right_impl(
            f,
            std::invoke(f, std::forward<RevNext>(rev_next), std::forward<RevHead>(rev_head)),
            std::forward<RevTail>(rev_tail)...
        );
    }
}

} // namespace yu::tuples::_detail

#endif
