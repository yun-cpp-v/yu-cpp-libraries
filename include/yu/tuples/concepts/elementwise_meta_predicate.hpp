// yutool: include guard
#ifndef YU_TUPLES_CONCEPTS_ELEMENTWISE_META_PREDICATE_HPP_
#define YU_TUPLES_CONCEPTS_ELEMENTWISE_META_PREDICATE_HPP_

#include <yu/meta/concepts.hpp>
#include <yu/meta/type.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _detail::elementwise_meta_predicate {

template <typename Pred, typename Tuple, std::size_t... Idx>
consteval bool impl(std::index_sequence<Idx...>) {
    return (
        meta::predicate<std::decay_t<Pred>, decltype(meta::as_type(tuples::get(std::declval<Tuple>(), index<Idx>)))>
        && ...
    );
}

} // namespace _detail::elementwise_meta_predicate

template <typename P, typename T>
concept elementwise_meta_predicate = tuple<T> && _detail::elementwise_meta_predicate::impl<P, T>(indices_for<T>);

} // namespace yu::tuples

#endif
