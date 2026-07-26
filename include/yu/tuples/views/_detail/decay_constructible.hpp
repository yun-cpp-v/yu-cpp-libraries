// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_DECAY_CONSTRUCTIBLE_HPP_
#define YU_TUPLES_VIEWS_DETAIL_DECAY_CONSTRUCTIBLE_HPP_

#include <concepts>
#include <type_traits>

namespace yu::tuples::_detail {

template <typename T>
concept decay_constructible = std::constructible_from<std::decay_t<T>, T>;

template <typename T>
inline constexpr bool is_nothrow_decay_constructible_v = std::is_nothrow_constructible_v<std::decay_t<T>, T>;

} // namespace yu::tuples::_detail

#endif
