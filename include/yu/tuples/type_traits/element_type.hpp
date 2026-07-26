// yutool: include guard
#ifndef YU_TUPLES_TYPE_TRAITS_ELEMENT_TYPE_HPP_
#define YU_TUPLES_TYPE_TRAITS_ELEMENT_TYPE_HPP_

#include "_detail/get_trait_base.hpp"
#include <cstddef>
#include <type_traits>

namespace yu::tuples {

template <std::size_t Idx, typename T>
struct element_type : _detail::get_trait_base<std::invoke_result, Idx, T> {};

template <std::size_t Idx, typename T>
using element_type_t = element_type<Idx, T>::type;

} // namespace yu::tuples

#endif