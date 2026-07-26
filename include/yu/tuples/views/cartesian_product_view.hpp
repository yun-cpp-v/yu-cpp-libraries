// yutool: include guard
#ifndef YU_TUPLES_VIEWS_CARTESIAN_PRODUCT_VIEW_HPP_
#define YU_TUPLES_VIEWS_CARTESIAN_PRODUCT_VIEW_HPP_

#include "all.hpp"
#include "single_view.hpp"
#include "view_interface.hpp"
#include <yu/meta/constant.hpp>
#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/access/size.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <array>
#include <tuple>
#include <utility>

namespace yu::tuples {

template <view... Views>
requires (0 < sizeof...(Views))
class cartesian_product_view : view_interface<cartesian_product_view<Views...>> {
    private:
        static consteval auto make_indices_table() {
            constexpr auto result = [] consteval {
                constexpr std::size_t dim        = sizeof...(Views);
                constexpr std::size_t table_size = (size_v<Views> * ... * 1);

                constexpr std::array<std::size_t, dim> sizes = {size_v<Views>...};

                using indices_t       = std::array<std::size_t, dim>;
                using indices_table_t = std::array<indices_t, table_size>;

                indices_table_t table{};
                indices_t       indices{};

                for (std::size_t linear = 0; linear < table_size; ++linear) {
                    table[linear] = indices;

                    for (std::size_t i = dim; i-- > 0;) {
                        if (++indices[i] < sizes[i]) break;

                        indices[i] = 0;
                    }
                }

                return table;
            }();

            return meta::constant<result>;
        }

        static constexpr auto indices_table_ = make_indices_table();
        using indices_table_t                = decltype(indices_table_)::value_type;

        std::tuple<Views...> base_;

        template <typename Self>
        constexpr decltype(auto) base(this Self&& self) noexcept {
            return std::forward_like<Self>(self.base_);
        }

        template <std::size_t Idx, typename Self>
        static consteval bool is_nothrow(Self&& self) {
            constexpr auto indices = indices_table_[index<Idx>];

            auto&& base = self.base();

            return []<std::size_t... Dims>(std::index_sequence<Dims...>) {
                return noexcept((tuples::get(tuples::get(base, index<Dims>), indices[index<Dims>]), ...));
            }(std::index_sequence_for<Views...>{});
        }

    public:
        static constexpr auto size = meta::constant_invoke(meta::constant<&indices_table_t::size>, indices_table_);

        constexpr explicit cartesian_product_view(Views... views) :
            base_(std::move(views)...) {}

        template <std::size_t Idx, typename Self>
        requires (Idx < size)
        constexpr decltype(auto) get(this Self&& self) noexcept(is_nothrow<Idx>(std::forward<Self>(self))) {
            constexpr auto indices = indices_table_[index<Idx>];

            auto&& base = self.base();

            return [&]<std::size_t... Dims>(std::index_sequence<Dims...>) {
                return std::forward_as_tuple(tuples::get(tuples::get(base, index<Dims>), indices[index<Dims>])...);
            }(std::index_sequence_for<Views...>{});
        }
};

template <typename... Tuples>
cartesian_product_view(Tuples&&...) -> cartesian_product_view<views::all_t<Tuples&&>...>;

namespace views {
namespace _unspecified {

struct cartesian_product_adaptor {
        template <tuple... Tuples>
        static constexpr auto operator()(Tuples&&... tuples) noexcept(noexcept(cartesian_product_view{
            std::forward<Tuples>(tuples)...
        })) {
            return cartesian_product_view{std::forward<Tuples>(tuples)...};
        }

        static constexpr auto operator()() noexcept { return single(std::tuple{}); }
};

} // namespace _unspecified

inline constexpr _unspecified::cartesian_product_adaptor cartesian_product{};

} // namespace views

} // namespace yu::tuples

#endif
