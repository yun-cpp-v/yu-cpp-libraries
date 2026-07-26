// yutool: include guard
#ifndef YU_TUPLES_CONCEPTS_ELEMENTWISE_UNARY_PREDICATE_HPP_
#define YU_TUPLES_CONCEPTS_ELEMENTWISE_UNARY_PREDICATE_HPP_

#include "tuple.hpp"
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <concepts>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _detail {

template <typename F, typename Tup, std::size_t... Idx>
consteval bool elementwise_unary_predicate_impl(std::index_sequence<Idx...>) {
    return (std::predicate<F, element_type_t<Idx, Tup>> && ...);
}

} // namespace _detail

// elementwise_unary_invocable
template <typename Fn, typename Tuple>
concept elementwise_unary_predicate
    = tuple<Tuple> && _detail::elementwise_unary_predicate_impl<Fn, Tuple>(indices_for<Tuple>);

} // namespace yu::tuples

#endif
