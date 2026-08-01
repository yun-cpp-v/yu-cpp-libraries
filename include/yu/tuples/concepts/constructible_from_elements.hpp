// yutool: include guard
#ifndef YU_TUPLES_CONCEPTS_CONSTRUCTIBLE_FROM_ELEMENTS_HPP_
#define YU_TUPLES_CONCEPTS_CONSTRUCTIBLE_FROM_ELEMENTS_HPP_

#include "tuple.hpp"
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <concepts>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _detail::constructible_from_elements {

template <typename T, typename Tuple, typename... Args, std::size_t... Idx>
consteval bool impl(std::index_sequence<Idx...>) {
    return std::constructible_from<T, element_type_t<Idx, Tuple>..., Args...>;
}

} // namespace _detail::constructible_from_elements

template <typename T, typename Tuple, typename... Args>
concept constructible_from_elements
    = tuple<Tuple> && _detail::constructible_from_elements::impl<T, Tuple, Args...>(indices_for<Tuple>);

} // namespace yu::tuples

#endif
