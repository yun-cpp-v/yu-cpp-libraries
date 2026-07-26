// yutool: include guard
#ifndef YU_TUPLES_VIEWS_TAKE_VIEW_HPP_
#define YU_TUPLES_VIEWS_TAKE_VIEW_HPP_

#include "_detail/take_view_base.hpp"
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
class take_view : public _detail::take_view_base<View, Count>, public view_interface<take_view<View, Count>> {
    private:
        using base_t = _detail::take_view_base<View, Count>;

    public:
        constexpr explicit take_view(View view, index_t<Count>) noexcept :
            base_t(std::move(view)) {}
};

template <typename Tuple, std::size_t Count>
take_view(Tuple&&, index_t<Count>) -> take_view<views::all_t<Tuple&&>, Count>;

namespace views {

namespace _unspecified {

struct take_adaptor {
        template <tuple Tuple, std::size_t Count>
        static constexpr auto operator()(Tuple&& tuple, index_t<Count> count) noexcept(
            noexcept(take_view{std::forward<Tuple>(tuple), count})
        ) {
            return take_view{std::forward<Tuple>(tuple), count};
        }

        template <std::size_t Count>
        static constexpr auto operator()(index_t<Count> count) noexcept {
            return make_partial_closure(take_adaptor{}, count);
        }
};

} // namespace _unspecified

inline constexpr _unspecified::take_adaptor take{};

} // namespace views

} // namespace yu::tuples

#endif
