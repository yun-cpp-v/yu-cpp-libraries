// yutool: include guard
#ifndef YU_TUPLES_ALGORITHM_DETAIL_RIGHT_FOLD_CONCEPTS_HPP_
#define YU_TUPLES_ALGORITHM_DETAIL_RIGHT_FOLD_CONCEPTS_HPP_

#include <yu/tuples/access/size.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples::_detail {

template <typename F, typename RevHead, typename RevNext, typename... RevTail>
consteval bool right_foldable_impl_impl() {
    constexpr bool current_step_invocable = std::invocable<F, RevNext, RevHead>;

    if constexpr (sizeof...(RevTail) == 0) {
        return current_step_invocable;
    } else {
        using fold_step_result = std::invoke_result_t<F, RevNext, RevHead>;

        return current_step_invocable && right_foldable_impl_impl<F, fold_step_result, RevTail...>();
    }
}

template <typename F, typename T, typename Tup, std::size_t... Idx>
consteval bool right_foldable_impl(std::index_sequence<Idx...>) {
    constexpr std::size_t size = size_v<Tup>;

    if constexpr (size == 0) {
        return true;
    } else {
        return right_foldable_impl_impl<F, element_type_t<size - Idx - 1, Tup>..., T>();
    }
}

template <typename F, typename Tup, std::size_t... Idx>
consteval bool right_foldable_last_impl(std::index_sequence<Idx...>) {
    constexpr std::size_t size = size_v<Tup>;

    if constexpr (size <= 2) {
        return false;
    } else {
        return right_foldable_impl_impl<F, element_type_t<size - Idx - 1, Tup>...>();
    }
}

template <typename F, typename T, typename Tup>
concept right_foldable = tuple<Tup> && right_foldable_impl<F, T, Tup>(indices_for<Tup>);

template <typename F, typename Tup>
concept right_foldable_last = tuple<Tup> && right_foldable_last_impl<F, Tup>(indices_for<Tup>);

} // namespace yu::tuples::_detail

#endif
