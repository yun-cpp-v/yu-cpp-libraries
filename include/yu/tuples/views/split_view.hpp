// yutool: include guard
#ifndef YU_TUPLES_VIEWS_SPLIT_VIEW_HPP_
#define YU_TUPLES_VIEWS_SPLIT_VIEW_HPP_

#include "_detail/meta_predicate_result_at.hpp"
#include "all.hpp"
#include "partial_closure.hpp"
#include "view_interface.hpp"
#include <yu/meta/concepts/predicate.hpp>
#include <yu/meta/constant.hpp>
#include <yu/meta/type.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/concepts/elementwise_meta_predicate.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <array>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _detail::split_view {

struct index_range {
        std::size_t begin;
        std::size_t end;
};

template <std::size_t N>
struct index_ranges {
        std::size_t                count;
        std::array<index_range, N> ranges;
};

} // namespace _detail::split_view

template <view View, typename Pred>
requires elementwise_meta_predicate<Pred, View>
class split_view : public view_interface<split_view<View, Pred>> {
    private:
        static consteval auto make_index_ranges() {
            constexpr auto result = []<std::size_t... Idx>(std::index_sequence<Idx...>) consteval {
                constexpr std::array  split_points = {!_detail::meta_predicate_result_at_v<Pred, View, Idx>...};
                constexpr std::size_t points_size  = split_points.size();

                using _detail::split_view::index_range;
                using _detail::split_view::index_ranges;

                std::array<index_range, points_size + 1> groups{};

                std::size_t range_count = 0;
                std::size_t range_begin = 0;

                for (std::size_t i = 0; i < points_size; ++i) {
                    if (split_points[i]) {
                        groups[range_count++] = {range_begin, i};

                        range_begin = i + 1;
                    }
                }

                groups[range_count++] = {range_begin, points_size};

                return index_ranges<points_size + 1>{range_count, groups};
            }(indices_for<View>);

            return meta::constant<result>;
        }

        static constexpr auto index_ranges_ = make_index_ranges();
        using index_ranges_t                = decltype(index_ranges_)::value_type;

        static constexpr auto ranges_ = meta::constant_invoke(meta::constant<&index_ranges_t::ranges>, index_ranges_);

        View base_;

        template <std::size_t Idx, typename Self>
        static consteval bool is_nothrow(Self&& self) {
            constexpr auto index_range = ranges_[index<Idx>];
            using index_range_t        = decltype(index_range)::value_type;

            constexpr std::size_t begin = meta::constant_invoke(meta::constant<&index_range_t::begin>, index_range);
            constexpr std::size_t end   = meta::constant_invoke(meta::constant<&index_range_t::end>, index_range);

            auto&& base = self.base();

            return []<std::size_t... I>(std::index_sequence<I...>) -> bool {
                return noexcept(((tuples::get(base, index<begin + I>)), ...));
            }(std::make_index_sequence<end - begin>{});
        }

    public:
        static constexpr auto size = meta::constant_invoke(meta::constant<&index_ranges_t::count>, index_ranges_);

        constexpr explicit split_view(View view, Pred) noexcept :
            base_(std::move(view)) {}

        template <typename Self>
        [[nodiscard]]
        constexpr decltype(auto) base(this Self&& self) noexcept {
            return std::forward_like<Self>(self.base_);
        }

        template <std::size_t Idx, typename Self>
        requires (Idx < size)
        [[nodiscard]]
        constexpr decltype(auto) get(this Self&& self) noexcept(is_nothrow<Idx>(std::forward<Self>(self))) {
            constexpr auto index_range = ranges_[index<Idx>];
            using index_range_t        = decltype(index_range)::value_type;

            constexpr std::size_t begin = meta::constant_invoke(meta::constant<&index_range_t::begin>, index_range);
            constexpr std::size_t end   = meta::constant_invoke(meta::constant<&index_range_t::end>, index_range);

            auto&& base = self.base();

            return [&]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto) {
                return std::forward_as_tuple(tuples::get(base, index<begin + I>)...);
            }(std::make_index_sequence<end - begin>{});
        }
};

template <typename Tuple, typename Pred>
split_view(Tuple&&, Pred) -> split_view<views::all_t<Tuple&&>, Pred>;

namespace views {

namespace _unspecified {

struct split_adaptor {
        template <tuple Tuple, typename Pred>
        requires elementwise_meta_predicate<Pred, Tuple>
        static constexpr auto operator()(Tuple&& tuple, Pred&& pred) noexcept(
            noexcept(split_view{std::forward<Tuple>(tuple), std::forward<Pred>(pred)})
        ) {
            return split_view{std::forward<Tuple>(tuple), std::forward<Pred>(pred)};
        }

        template <typename P>
        static constexpr auto operator()(P&& pred) noexcept {
            return make_partial_closure(split_adaptor{}, std::forward<P>(pred));
        }
};

} // namespace _unspecified

inline constexpr _unspecified::split_adaptor split;

} // namespace views

} // namespace yu::tuples

#endif
