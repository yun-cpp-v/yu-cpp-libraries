// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_COMPOSED_CLOSURE_HPP_
#define YU_TUPLES_VIEWS_DETAIL_COMPOSED_CLOSURE_HPP_

#include "tuple_adaptor_closure_base.hpp"
#include <yu/tuples/concepts/tuple.hpp>
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
        static consteval bool invocable() {
            return requires(Self&& self, Tuple&& tuple) {
                std::invoke(self.closure2(), std::invoke(self.closure1(), std::forward<Tuple>(tuple)));
            };
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
        constexpr explicit composed_closure(Closure1&& closure1, Closure2&& closure2) noexcept(
            std::is_nothrow_move_constructible_v<Closure1> && std::is_nothrow_move_constructible_v<Closure2>
        ) :
            closure1_(std::move(closure1)), closure2_(std::move(closure2)) {}

        template <typename Self, tuples::tuple Tuple>
        requires (invocable<Self, Tuple>())
        [[nodiscard]]
        constexpr decltype(auto) operator()(this Self&& self, Tuple&& tuple) noexcept(
            nothrow(std::invoke(self.closure2(), std::invoke(self.closure1(), std::forward<Tuple>(tuple))))
        ) {
            return std::invoke(self.closure2(), std::invoke(self.closure1(), std::forward<Tuple>(tuple)));
        }
};

template <typename T1, typename T2>
composed_closure(T1, T2) -> composed_closure<T1, T2>;

} // namespace yu::tuples::_detail

#endif
