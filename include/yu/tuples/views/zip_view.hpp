// yutool: include guard
#ifndef YU_TUPLES_VIEWS_ZIP_VIEW_HPP_
#define YU_TUPLES_VIEWS_ZIP_VIEW_HPP_

#include "all.hpp"
#include "empty_view.hpp"
#include "view_interface.hpp"
#include "yu/tuples/access/get.hpp"
#include <yu/meta/constant.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/apply.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <algorithm>
#include <tuple>
#include <utility>

namespace yu::tuples {

template <view... Views>
requires (0 < sizeof...(Views))
class zip_view : public view_interface<zip_view<Views...>> {
    private:
        std::tuple<Views...> base_;

        template <typename Self>
        constexpr decltype(auto) base(this Self&& self) noexcept {
            return std::forward_like<Self>(self.base_);
        }

        template <std::size_t Idx, typename Self>
        static consteval bool is_nothrow(Self&& self) {
            return tuples::apply(
                [&]<typename... Elems>(Elems&&... views) { return noexcept((tuples::get(views, index<Idx>), ...)); },
                self.base()
            );
        }

    public:
        static constexpr index_t<std::min({size_v<Views>...})> size{};

        constexpr explicit zip_view(Views... views) :
            base_(std::move(views)...) {}

        template <std::size_t Idx, typename Self>
        requires (Idx < size)
        constexpr decltype(auto) get(this Self&& self) noexcept(is_nothrow<Idx>(std::forward<Self>(self))) {
            return tuples::apply(
                [&]<typename... Elems>(Elems&&... views) {
                    return std::forward_as_tuple(tuples::get(views, index<Idx>)...);
                },
                self.base()
            );
        }
};

template <typename... Views>
zip_view(Views&&...) -> zip_view<views::all_t<Views&&>...>;

namespace views {
namespace _unspecified {

struct zip_adaptor {
        template <tuple... Tuples>
        requires (0 < sizeof...(Tuples))
        static constexpr auto operator()(Tuples&&... tuples) noexcept(noexcept(zip_view{
            std::forward<Tuples>(tuples)...
        })) {
            return zip_view{std::forward<Tuples>(tuples)...};
        }

        static constexpr auto operator()() noexcept { return empty; }
};

} // namespace _unspecified

inline constexpr _unspecified::zip_adaptor zip{};

} // namespace views

} // namespace yu::tuples

#endif
