// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_ADAPTOR_CLOSURE_HPP_
#define YU_TUPLES_VIEWS_DETAIL_ADAPTOR_CLOSURE_HPP_

#include "tuple_adaptor_closure_base.hpp"
#include <concepts>
#include <type_traits>

namespace yu::tuples::_detail {

template <typename T>
concept adaptor_closure = std::derived_from<std::remove_cvref_t<T>, tuple_adaptor_closure<std::remove_cvref_t<T>>>;

} // namespace yu::tuples::_detail

#endif