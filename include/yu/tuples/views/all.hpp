// yutool: include guard
#ifndef YU_TUPLES_VIEWS_ALL_HPP_
#define YU_TUPLES_VIEWS_ALL_HPP_

#include "owning_view.hpp"
#include "ref_view.hpp"
#include "tuple_adaptor_closure.hpp"
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <type_traits>
#include <utility>

namespace yu::tuples {

namespace views {

namespace _detail::all {

template <typename Tuple>
concept ref_viewable = requires(Tuple&& tuple) { ref_view{std::forward<Tuple>(tuple)}; };

template <typename Tuple>
concept owning_viewable = requires(Tuple&& tuple) { owning_view{std::forward<Tuple>(tuple)}; };

} // namespace _detail::all

namespace _unspecified {

struct all_closure : tuple_adaptor_closure<all_closure> {
    private:
        template <typename Tuple>
        static consteval bool is_nothrow(Tuple&& tuple) {
            if constexpr (view<std::remove_cvref_t<Tuple>>) {
                return noexcept(auto(std::forward<Tuple>(tuple)));
            } else if constexpr (_detail::all::ref_viewable<Tuple>) {
                return noexcept(ref_view{std::forward<Tuple>(tuple)});
            } else if constexpr (_detail::all::owning_viewable<Tuple>) {
                return noexcept(owning_view{std::forward<Tuple>(tuple)});
            }
        }

    public:
        template <tuple Tuple>
        requires (
            view<std::remove_cvref_t<Tuple>> || _detail::all::ref_viewable<Tuple>
            || _detail::all::owning_viewable<Tuple>
        )
        [[nodiscard]]
        static constexpr auto operator()(Tuple&& tuple) noexcept(is_nothrow(std::forward<Tuple>(tuple))) {
            if constexpr (view<std::remove_cvref_t<Tuple>>) {
                return auto(std::forward<Tuple>(tuple));
            } else if constexpr (_detail::all::ref_viewable<Tuple>) {
                return ref_view{std::forward<Tuple>(tuple)};
            } else if constexpr (_detail::all::owning_viewable<Tuple>) {
                return owning_view{std::forward<Tuple>(tuple)};
            }
        }
};

} // namespace _unspecified

inline constexpr _unspecified::all_closure all{};

template <tuple Tuple>
using all_t = decltype(all(std::declval<Tuple>()));

} // namespace views

template <_detail::adaptor_closure Closure>
[[nodiscard]]
constexpr decltype(auto) operator|(const decltype(views::all)&, Closure&& closure) noexcept {
    return std::forward<Closure>(closure);
}

template <_detail::adaptor_closure Closure>
[[nodiscard]]
constexpr decltype(auto) operator|(Closure&& closure, const decltype(views::all)&) noexcept {
    return std::forward<Closure>(closure);
}

[[nodiscard]]
constexpr auto operator|(const decltype(views::all)&, const decltype(views::all)&) noexcept {
    return views::all;
}

} // namespace yu::tuples

#endif
