// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_DIFFERENT_FROM_HPP_
#define YU_TUPLES_VIEWS_DETAIL_DIFFERENT_FROM_HPP_

#include <concepts>
#include <type_traits>

namespace yu::tuples::_detail {

template <typename T, typename U>
concept different_from = !std::same_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;

} // namespace yu::tuples::_detail

#endif
