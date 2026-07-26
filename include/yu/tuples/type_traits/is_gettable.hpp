// yutool: include guard
#ifndef YU_TUPLES_TYPE_TRAITS_IS_GETTABLE_HPP_
#define YU_TUPLES_TYPE_TRAITS_IS_GETTABLE_HPP_

#include "_detail/get_trait_base.hpp"
#include <cstddef>
#include <type_traits>

namespace yu::tuples {

template <std::size_t Idx, typename T>
struct is_gettable : _detail::get_trait_base<std::is_invocable, Idx, T, std::false_type> {};

template <std::size_t Idx, typename T>
inline constexpr bool is_gettable_v = is_gettable<Idx, T>::value;

template <std::size_t Idx, typename T>
struct is_nothrow_gettable : _detail::get_trait_base<std::is_nothrow_invocable, Idx, T, std::false_type> {};

template <std::size_t Idx, typename T>
inline constexpr bool is_nothrow_gettable_v = is_nothrow_gettable<Idx, T>::value;

} // namespace yu::tuples

#endif
