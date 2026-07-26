// yutool: include guard
#ifndef YU_TUPLES_CONCEPTS_ELEMENTWISE_UNARY_INVOCABLE_HPP_
#define YU_TUPLES_CONCEPTS_ELEMENTWISE_UNARY_INVOCABLE_HPP_

#include "tuple.hpp"
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <concepts>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _detail {

template <typename Fn, typename Tuple, std::size_t... Idx>
consteval bool elementwise_unary_invocable_impl(std::index_sequence<Idx...>) {
    return (std::invocable<Fn, element_type_t<Idx, Tuple>> && ...);
}

} // namespace _detail

template <typename Fn, typename Tuple>
concept elementwise_unary_invocable
    = tuple<Tuple> && _detail::elementwise_unary_invocable_impl<Fn, Tuple>(indices_for<Tuple>);

template <typename Fn, typename Tuple>
concept elementwise_unary_regular_invocable = elementwise_unary_invocable<Fn, Tuple>;

} // namespace yu::tuples

#endif
