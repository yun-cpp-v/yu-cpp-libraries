// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_META_PREDICATE_RESULT_AT_HPP_
#define YU_TUPLES_VIEWS_DETAIL_META_PREDICATE_RESULT_AT_HPP_

#include <yu/meta/type.hpp>
#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <cstddef>
#include <functional>

namespace yu::tuples::_detail {

template <typename Pred, typename Tuple, std::size_t Idx>
inline constexpr bool meta_predicate_result_at_v
    = decltype(std::invoke(std::declval<Pred>(), meta::as_type(tuples::get(std::declval<Tuple>(), index<Idx>))))::value;

} // namespace yu::tuples::_detail

#endif
