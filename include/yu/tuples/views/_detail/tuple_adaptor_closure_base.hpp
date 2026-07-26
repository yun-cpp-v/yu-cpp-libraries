// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_TUPLE_ADAPTOR_CLOSURE_BASE_HPP_
#define YU_TUPLES_VIEWS_DETAIL_TUPLE_ADAPTOR_CLOSURE_BASE_HPP_

#include <concepts>
#include <type_traits>

namespace yu::tuples {

template <typename D>
requires std::is_class_v<D> && std::same_as<D, std::remove_cv_t<D>>
struct tuple_adaptor_closure {};

namespace _detail {

template <typename T>
concept adaptor_closure = std::derived_from<std::remove_cvref_t<T>, tuple_adaptor_closure<std::remove_cvref_t<T>>>;

} // namespace _detail

} // namespace yu::tuples

#endif
