// yutool: include guard
#ifndef YU_TUPLES_TYPE_TRAITS_IS_APPLICABLE_HPP_
#define YU_TUPLES_TYPE_TRAITS_IS_APPLICABLE_HPP_

#include "_detail/apply_trait_base.hpp"
#include <type_traits>

namespace yu::tuples {

template <typename Fn, typename Tuple>
struct is_applicable : _detail::apply_trait_base<std::is_invocable, Tuple, Fn> {};

template <typename Fn, typename Tuple>
inline constexpr bool is_applicable_v = is_applicable<Fn, Tuple>::value;

template <typename Ret, typename Fn, typename Tuple>
struct is_applicable_r : _detail::apply_trait_base<std::is_invocable_r, Tuple, Fn, Ret> {};

template <typename Ret, typename Fn, typename Tuple>
inline constexpr bool is_applicable_r_v = is_applicable_r<Ret, Fn, Tuple>::value;

template <typename Fn, typename Tuple>
struct is_nothrow_applicable : _detail::apply_trait_base<std::is_nothrow_invocable, Tuple, Fn> {};

template <typename Fn, typename Tuple>
inline constexpr bool is_nothrow_applicable_v = is_nothrow_applicable<Fn, Tuple>::value;

template <typename Ret, typename Fn, typename Tuple>
struct is_nothrow_applicable_r : _detail::apply_trait_base<std::is_nothrow_invocable_r, Tuple, Fn, Ret> {};

template <typename Ret, typename Fn, typename Tuple>
inline constexpr bool is_nothrow_applicable_r_v = is_nothrow_applicable_r<Ret, Fn, Tuple>::value;

} // namespace yu::tuples

#endif
