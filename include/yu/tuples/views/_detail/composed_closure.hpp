// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_COMPOSED_CLOSURE_HPP_
#define YU_TUPLES_VIEWS_DETAIL_COMPOSED_CLOSURE_HPP_

#include "tuple_adaptor_closure_base.hpp"
#include <yu/tuples/concepts/tuple.hpp>
#include <concepts>
#include <functional>
#include <type_traits>
#include <utility>

namespace yu::tuples::_detail {

template <typename Closure1, typename Closure2>
struct composed_closure : tuple_adaptor_closure<composed_closure<Closure1, Closure2>> {
    private:
        [[no_unique_address]]
        Closure1 closure1_;
        [[no_unique_address]]
        Closure2 closure2_;

        template <typename Self, typename Tuple>
        static consteval bool invocable(Self&& self, Tuple&& tuple) {
            return requires { std::invoke(self.closure2(), std::invoke(self.closure1(), std::forward<Tuple>(tuple))); };
        }

        template <typename Self, typename Tuple>
        static consteval bool is_nothrow(Self&& self, Tuple&& tuple) {
            return noexcept(std::invoke(self.closure2(), std::invoke(self.closure1(), std::forward<Tuple>(tuple))));
        }

        template <typename Self>
        constexpr decltype(auto) closure1(this Self&& self) noexcept {
            return std::forward_like<Self>(self.closure1_);
        }

        template <typename Self>
        constexpr decltype(auto) closure2(this Self&& self) noexcept {
            return std::forward_like<Self>(self.closure2_);
        }

    public:
        template <typename T1, typename T2>
        requires std::constructible_from<Closure1, T1&&> && std::constructible_from<Closure2, T2&&>
        constexpr explicit composed_closure(T1&& cl1, T2&& cl2) noexcept(
            std::is_nothrow_constructible_v<Closure1, T1&&> && std::is_nothrow_constructible_v<Closure2, T2&&>
        ) :
            closure1_(std::forward<T1>(cl1)), closure2_(std::forward<T2>(cl2)) {}

        template <typename Self, tuple Tuple>
        [[nodiscard]]
        constexpr decltype(auto) operator()(this Self&& self, Tuple&& tuple) noexcept(
            is_nothrow(std::forward<Self>(self), std::forward<Tuple>(tuple))
        ) requires (invocable(std::forward<Self>(self), std::forward<Tuple>(tuple)))
        {
            return std::invoke(self.closure2(), std::invoke(self.closure1(), std::forward<Tuple>(tuple)));
        }
};

template <typename T1, typename T2>
composed_closure(T1, T2) -> composed_closure<T1, T2>;

template <typename Closure1, typename Closure2>
constexpr auto compose_closures(Closure1&& closure1, Closure2&& closure2) {
    return composed_closure{std::forward<Closure1>(closure1), std::forward<Closure2>(closure2)};
}

} // namespace yu::tuples::_detail

#endif
