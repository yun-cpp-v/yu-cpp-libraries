// yutool: include guard
#ifndef YU_TUPLES_VIEWS_CONCAT_VIEW_HPP_
#define YU_TUPLES_VIEWS_CONCAT_VIEW_HPP_

#include "_detail/flatten_view_base.hpp"
#include "all.hpp"
#include "view_interface.hpp"
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <tuple>
#include <type_traits>
#include <utility>

namespace yu::tuples {

template <view... Views>
class concat_view :
    public _detail::flatten_view_base<std::tuple<Views...>>,
    public view_interface<concat_view<Views...>> {
    private:
        using base_tuple_t = std::tuple<Views...>;
        using base_t       = _detail::flatten_view_base<base_tuple_t>;

    public:
        constexpr explicit concat_view(Views... views) noexcept(
            std::is_nothrow_constructible_v<base_tuple_t, Views&&...>
            && std::is_nothrow_constructible_v<base_t, base_tuple_t>
        ) :
            base_t(base_tuple_t{std::move(views)...}) {}
};

template <typename... Tuples>
concat_view(Tuples&&...) -> concat_view<views::all_t<Tuples&&>...>;

namespace views {
namespace _unspecified::concat {

struct adaptor {
        template <tuple... Tuples>
        static constexpr auto operator()(Tuples&&... tuples) noexcept(noexcept(concat_view{
            std::forward<Tuples>(tuples)...
        })) {
            return concat_view{std::forward<Tuples>(tuples)...};
        }
};

} // namespace _unspecified::concat

inline constexpr _unspecified::concat::adaptor concat{};

} // namespace views

} // namespace yu::tuples

#endif
