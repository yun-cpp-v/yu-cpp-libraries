// yutool: include guard
#ifndef YU_TUPLES_VIEWS_FILTER_VIEW_HPP_
#define YU_TUPLES_VIEWS_FILTER_VIEW_HPP_

#include "_detail/meta_predicate_result_at.hpp"
#include "all.hpp"
#include "partial_closure.hpp"
#include "view_interface.hpp"
#include <yu/meta/concepts/predicate.hpp>
#include <yu/meta/constant.hpp>
#include <yu/meta/type.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/concepts/elementwise_meta_predicate.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <array>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _detail::filter_view {

template <std::size_t N>
struct selected_indices {
        std::size_t                count;
        std::array<std::size_t, N> indices;
};

} // namespace _detail::filter_view

template <view View, typename Pred>
requires elementwise_meta_predicate<Pred, View>
class filter_view : public view_interface<filter_view<View, Pred>> {
    private:
        static consteval auto select_indices() {
            constexpr auto result = []<std::size_t... Idx>(std::index_sequence<Idx...>) consteval {
                constexpr std::array  selected      = {_detail::meta_predicate_result_at_v<Pred, View, Idx>...};
                constexpr std::size_t selected_size = selected.size();

                std::array<std::size_t, selected_size> indices{};

                std::size_t selected_index_count = 0;

                for (std::size_t i = 0; i < selected_size; ++i) {
                    if (selected[i]) indices[selected_index_count++] = i;
                }

                using selected_t = _detail::filter_view::selected_indices<selected_size>;

                return selected_t{selected_index_count, indices};
            }(indices_for<View>);

            return meta::constant<result>;
        }

        static constexpr auto selected_indices_ = select_indices();
        using selected_indices_t                = decltype(selected_indices_)::value_type;

        static constexpr auto indices_
            = meta::constant_invoke(meta::constant<&selected_indices_t::indices>, selected_indices_);

        View base_;

    public:
        static constexpr auto size
            = meta::constant_invoke(meta::constant<&selected_indices_t::count>, selected_indices_);

        constexpr explicit filter_view(View view, Pred) noexcept :
            base_(std::move(view)) {}

        template <typename Self>
        [[nodiscard]]
        constexpr decltype(auto) base(this Self&& self) noexcept {
            return std::forward_like<Self>(self.base_);
        }

        template <std::size_t Idx, typename Self>
        requires (Idx < size)
        [[nodiscard]]
        constexpr decltype(auto) get(this Self&& self) noexcept(
            noexcept(tuples::get(self.base(), indices_[index<Idx>]))
        ) {
            return tuples::get(self.base(), indices_[index<Idx>]);
        }
};

template <typename T, typename P>
filter_view(T&&, P) -> filter_view<views::all_t<T&&>, P>;

namespace views {

namespace _unspecified {

struct filter_adaptor {
        template <tuple Tuple, typename Pred>
        requires elementwise_meta_predicate<Pred, Tuple>
        static constexpr auto operator()(Tuple&& tuple, Pred&& pred) noexcept(
            noexcept(filter_view{std::forward<Tuple>(tuple), std::forward<Pred>(pred)})
        ) {
            return filter_view{std::forward<Tuple>(tuple), std::forward<Pred>(pred)};
        }

        template <typename P>
        static constexpr auto operator()(P&& pred) noexcept {
            return make_partial_closure(filter_adaptor{}, std::forward<P>(pred));
        }
};

} // namespace _unspecified

inline constexpr _unspecified::filter_adaptor filter;

} // namespace views

} // namespace yu::tuples

#endif
