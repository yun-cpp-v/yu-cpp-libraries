// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DROP_VIEW_HPP_
#define YU_TUPLES_VIEWS_DROP_VIEW_HPP_

#include "_detail/drop_view_base.hpp"
#include "all.hpp"
#include "partial_closure.hpp"
#include "view_interface.hpp"
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples {

template <view View, std::size_t Count>
class drop_view : public _detail::drop_view_base<View, Count>, public view_interface<drop_view<View, Count>> {
    private:
        using base_t = _detail::drop_view_base<View, Count>;

    public:
        constexpr explicit drop_view(View view, index_t<Count>) noexcept :
            base_t(std::move(view)) {}
};

template <typename Tuple, std::size_t Count>
drop_view(Tuple&&, index_t<Count>) -> drop_view<views::all_t<Tuple&&>, Count>;

namespace views {

namespace _unspecified::drop {

struct adaptor {
        template <tuple Tuple, std::size_t Count>
        static constexpr auto operator()(Tuple&& tuple, index_t<Count> count) noexcept(
            noexcept(drop_view{std::forward<Tuple>(tuple), count})
        ) {
            return drop_view{std::forward<Tuple>(tuple), count};
        }

        template <std::size_t Count>
        static constexpr auto operator()(index_t<Count> count) noexcept {
            return make_partial_closure(adaptor{}, count);
        }
};

} // namespace _unspecified::drop

inline constexpr _unspecified::drop::adaptor drop{};

} // namespace views

} // namespace yu::tuples

#endif
