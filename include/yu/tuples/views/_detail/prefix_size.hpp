// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_PREFIX_SIZE_HPP_
#define YU_TUPLES_VIEWS_DETAIL_PREFIX_SIZE_HPP_

#include "meta_predicate_result_at.hpp"
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples::_detail {

template <typename T, typename Pred, std::size_t... Idx>
consteval std::size_t prefix_size_impl(std::index_sequence<Idx...>) {
    std::size_t result = 0;
    (void)(((meta_predicate_result_at_v<Pred, T, Idx>) && (++result, true)) && ...);
    return result;
}

template <typename T, typename Pred>
inline constexpr std::size_t prefix_size = prefix_size_impl<T, Pred>(indices_for<T>);

} // namespace yu::tuples::_detail

#endif
