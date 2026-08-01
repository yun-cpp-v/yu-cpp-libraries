// yutool: include guard
#ifndef YU_TUPLES_VIEWS_TUPLE_ADAPTOR_CLOSURE_HPP_
#define YU_TUPLES_VIEWS_TUPLE_ADAPTOR_CLOSURE_HPP_

#include "_detail/adaptor_closure.hpp"
#include "_detail/composed_closure.hpp"
#include <yu/tuples/concepts/tuple.hpp>
#include <concepts>
#include <functional>
#include <type_traits>
#include <utility>
//
#include "_detail/tuple_adaptor_closure_base.hpp" // IWYU pragma: export

namespace yu::tuples {

template <typename D>
requires std::is_class_v<D> && std::same_as<D, std::remove_cv_t<D>>
struct tuple_adaptor_closure;

template <tuple Tuple, _detail::adaptor_closure Closure>
requires std::invocable<Closure, Tuple&&>
[[nodiscard]]
constexpr decltype(auto) operator|(Tuple&& tuple, Closure&& closure) noexcept(
    std::is_nothrow_invocable_v<Closure, Tuple&&>
) {
    return std::invoke(std::forward<Closure>(closure), std::forward<Tuple>(tuple));
}

template <_detail::adaptor_closure Closure1, _detail::adaptor_closure Closure2>
[[nodiscard]]
constexpr auto operator|(Closure1&& closure1, Closure2&& closure2) noexcept(
    _detail::composed_closure{std::forward<Closure1>(closure1), std::forward<Closure2>(closure2)}
) {
    return _detail::composed_closure{std::forward<Closure1>(closure1), std::forward<Closure2>(closure2)};
}

} // namespace yu::tuples

#endif
