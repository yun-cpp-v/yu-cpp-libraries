// yutool: include guard
#ifndef YU_TUPLES_VIEWS_ENABLE_VIEW_HPP_
#define YU_TUPLES_VIEWS_ENABLE_VIEW_HPP_

#include "view_base.hpp"
#include "view_interface.hpp"
#include <concepts>

namespace yu::tuples {

template <class T>
inline constexpr bool enable_view = std::derived_from<T, view_base> || std::derived_from<T, view_interface<T>>;

} // namespace yu::tuples

#endif
