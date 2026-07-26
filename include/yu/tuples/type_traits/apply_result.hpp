// yutool: include guard
#ifndef YU_TUPLES_TYPE_TRAITS_APPLY_RESULT_HPP_
#define YU_TUPLES_TYPE_TRAITS_APPLY_RESULT_HPP_

#include "_detail/apply_trait_base.hpp"
#include <type_traits>

namespace yu::tuples {

template <typename Fn, typename T>
struct apply_result : _detail::apply_trait_base<std::invoke_result, T, Fn> {};

template <typename Fn, typename T>
using apply_result_t = apply_result<Fn, T>::type;

} // namespace yu::tuples

#endif