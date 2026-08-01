// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_TUPLE_OF_TUPLES_HPP_
#define YU_TUPLES_VIEWS_DETAIL_TUPLE_OF_TUPLES_HPP_

#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples::_detail {

template <typename T, std::size_t... Idx>
consteval bool tuple_of_tuples_impl(std::index_sequence<Idx...>) {
    return (tuples::tuple<element_type_t<Idx, T>> && ...);
}

template <typename T>
concept tuple_of_tuples = tuples::tuple<T> && tuple_of_tuples_impl<T>(indices_for<T>);

} // namespace yu::tuples::_detail

#endif