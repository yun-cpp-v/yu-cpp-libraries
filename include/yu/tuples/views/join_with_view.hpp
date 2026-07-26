// yutool: include guard
#ifndef YU_TUPLES_VIEWS_JOIN_WITH_VIEW_HPP_
#define YU_TUPLES_VIEWS_JOIN_WITH_VIEW_HPP_

#include "_detail/flatten_view_base.hpp"
#include "_detail/tuple_of_tuples.hpp"
#include "all.hpp"
#include "partial_closure.hpp"
#include "single_view.hpp"
#include "view_interface.hpp"
#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/access/size.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <yu/tuples/views/single_view.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _detail::join_with_view {

template <typename View, typename Pattern>
struct separator_insert_view : public tuples::view_interface<separator_insert_view<View, Pattern>> {
        View    base;
        Pattern pattern;

        static constexpr index_t<2 * size_v<View> - 1> size{};

        template <std::size_t Idx, typename Self>
        constexpr decltype(auto) get(this Self&& self) {
            if constexpr (Idx % 2 == 0) {
                return tuples::get(std::forward_like<Self>(self.base), index<Idx / 2>);
            } else {
                return std::forward_like<Self>(self.pattern);
            }
        }
};

} // namespace _detail::join_with_view

template <view View, view Pattern>
requires _detail::tuple_of_tuples<View>
class join_with_view :
    public _detail::flatten_view_base<_detail::join_with_view::separator_insert_view<View, Pattern>>,
    public view_interface<join_with_view<View, Pattern>> {
    private:
        using inserter_t = _detail::join_with_view::separator_insert_view<View, Pattern>;
        using base_t     = _detail::flatten_view_base<inserter_t>;

    public:
        constexpr explicit join_with_view(View view, Pattern pattern) noexcept :
            base_t(inserter_t{.base = std::move(view), .pattern = std::move(pattern)}) {}
};

template <typename Tuple, typename Pattern>
join_with_view(Tuple&&, Pattern&&) -> join_with_view<views::all_t<Tuple&&>, views::all_t<Pattern&&>>;

namespace views {
namespace _unspecified {

struct join_with_adaptor {
        template <tuple Tuple, tuple Pattern>
        requires tuples::_detail::tuple_of_tuples<Tuple>
        static constexpr auto operator()(Tuple&& tuple, Pattern&& pattern) noexcept(
            noexcept(join_with_view{std::forward<Tuple>(tuple), std::forward<Pattern>(pattern)})
        ) {
            return join_with_view{std::forward<Tuple>(tuple), std::forward<Pattern>(pattern)};
        }

        template <tuple Tuple, typename Pattern>
        requires tuples::_detail::tuple_of_tuples<Tuple>
        static constexpr auto operator()(Tuple&& tuple, Pattern&& pattern) noexcept(
            noexcept(join_with_view{std::forward<Tuple>(tuple), single(std::forward<Pattern>(pattern))})
        ) {
            return join_with_view{std::forward<Tuple>(tuple), single(std::forward<Pattern>(pattern))};
        }

        template <tuple Pattern>
        static constexpr auto operator()(Pattern&& pattern) noexcept(
            noexcept(views::all(std::forward<Pattern>(pattern)))
        ) {
            return make_partial_closure(join_with_adaptor{}, views::all(std::forward<Pattern>(pattern)));
        }

        template <typename Pattern>
        static constexpr auto operator()(Pattern&& pattern) noexcept {
            return make_partial_closure(join_with_adaptor{}, std::forward<Pattern>(pattern));
        }
};

} // namespace _unspecified

inline constexpr _unspecified::join_with_adaptor join_with{};

} // namespace views
} // namespace yu::tuples

#endif
