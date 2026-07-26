// yutool: include guard
#ifndef YU_TUPLES_VIEWS_INDICES_VIEW_HPP_
#define YU_TUPLES_VIEWS_INDICES_VIEW_HPP_

#include "iota_view.hpp"
#include <cstddef>

namespace yu::tuples {

template <std::size_t Size>
using indices_view = iota_view<0, Size>;

namespace views {

namespace _unspecified {

struct indices_fn {
        template <std::size_t Size>
        [[nodiscard]]
        static constexpr auto operator()(index_t<Size>) noexcept {
            return indices_view<Size>{};
        }
};

} // namespace _unspecified

inline constexpr _unspecified::indices_fn indices{};

} // namespace views

} // namespace yu::tuples

#endif