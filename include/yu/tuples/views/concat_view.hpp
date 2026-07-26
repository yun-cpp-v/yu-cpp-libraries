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
#include <utility>

namespace yu::tuples {

template <view... Views>
class concat_view :
    public _detail::flatten_view_base<std::tuple<Views...>>,
    public view_interface<concat_view<Views...>> {
    private:
        using base_t = _detail::flatten_view_base<std::tuple<Views...>>;

    public:
        constexpr explicit concat_view(Views... views) noexcept :
            base_t(std::tuple<Views...>{std::move(views)...}) {}
};

template <typename... Tuples>
concat_view(Tuples&&...) -> concat_view<views::all_t<Tuples&&>...>;

namespace views {
namespace _unspecified {

struct concat_adaptor {
        template <tuple... Tuples>
        static constexpr auto operator()(Tuples&&... tuples) noexcept(noexcept(concat_view{
            std::forward<Tuples>(tuples)...
        })) {
            return concat_view{std::forward<Tuples>(tuples)...};
        }
};

} // namespace _unspecified

inline constexpr _unspecified::concat_adaptor concat{};

} // namespace views

} // namespace yu::tuples

#endif
