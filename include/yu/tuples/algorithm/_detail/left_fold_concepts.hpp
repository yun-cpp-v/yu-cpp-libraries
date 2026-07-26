// yutool: include guard
#ifndef YU_TUPLES_ALGORITHM_DETAIL_LEFT_FOLD_CONCEPTS_HPP_
#define YU_TUPLES_ALGORITHM_DETAIL_LEFT_FOLD_CONCEPTS_HPP_

#include <yu/tuples/access/size.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples::_detail {

template <typename F, typename Head, typename Next, typename... Tail>
consteval bool left_foldable_impl_impl() {
    constexpr bool current_step_invocable = std::invocable<F, Head, Next>;

    if constexpr (sizeof...(Tail) == 0) {
        return current_step_invocable;
    } else {
        using fold_step_result = std::invoke_result_t<F, Head, Next>;

        return current_step_invocable && left_foldable_impl_impl<F, fold_step_result, Tail...>();
    }
}

template <typename F, typename T, typename Tup, std::size_t... Idx>
consteval bool left_foldable_impl(std::index_sequence<Idx...>) {
    if constexpr (size_v<Tup> == 0) {
        return true;
    } else {
        return left_foldable_impl_impl<F, T, element_type_t<Idx, Tup>...>();
    }
}

template <typename F, typename Tup, std::size_t... Idx>
consteval bool left_folable_first_impl(std::index_sequence<Idx...>) {
    if constexpr (size_v<Tup> <= 2) {
        return false;
    } else {
        return left_foldable_impl_impl<F, element_type_t<Idx, Tup>...>();
    }
}

template <typename F, typename T, typename Tup>
concept left_foldable = tuple<Tup> && left_foldable_impl<F, T, Tup>(indices_for<Tup>);

template <typename F, typename Tup>
concept left_foldable_first = tuple<Tup> && left_folable_first_impl<F, Tup>(indices_for<Tup>);

} // namespace yu::tuples::_detail

#endif
