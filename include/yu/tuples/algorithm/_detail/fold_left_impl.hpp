// yutool: include guard
#ifndef YU_TUPLES_ALGORITHM_DETAIL_FOLD_LEFT_IMPL_HPP_
#define YU_TUPLES_ALGORITHM_DETAIL_FOLD_LEFT_IMPL_HPP_

#include <functional>
#include <utility>

namespace yu::tuples::_detail {

template <typename F, typename Head, typename Next, typename... Tail>
constexpr decltype(auto) fold_left_impl(F& f, Head&& head, Next&& next, Tail&&... tail) {
    if constexpr (sizeof...(Tail) == 0) {
        return std::invoke(f, std::forward<Head>(head), std::forward<Next>(next));
    } else {
        return fold_left_impl(
            f,
            std::invoke(f, std::forward<Head>(head), std::forward<Next>(next)),
            std::forward<Tail>(tail)...
        );
    }
}

} // namespace yu::tuples::_detail

#endif
