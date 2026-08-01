// yutool: include guard
#ifndef YU_TUPLES_VIEWS_DETAIL_FLATTEN_VIEW_BASE_HPP_
#define YU_TUPLES_VIEWS_DETAIL_FLATTEN_VIEW_BASE_HPP_

#include <yu/meta/constant.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/access/size.hpp>
#include <yu/tuples/concepts/view.hpp>
#include <yu/tuples/type_traits/element_type.hpp>
#include <yu/tuples/type_traits/is_gettable.hpp>
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <cstddef>
#include <utility>

namespace yu::tuples::_detail {

struct mapped_index {
        std::size_t base_index;
        std::size_t inner_index;
};

template <typename Base>
class flatten_view_base {
    private:
        static consteval auto make_index_map() {
            constexpr auto result = []<std::size_t... Idx>(std::index_sequence<Idx...>) consteval {
                constexpr std::size_t total_size   = (size_v<element_type_t<Idx, Base>> + ...);
                constexpr std::size_t view_sizes[] = {size_v<element_type_t<Idx, Base>>...};

                std::array<mapped_index, total_size> index_map{};

                for (std::size_t total_index = 0; total_index < total_size; ++total_index) {
                    std::size_t base_index = 0, inner_index = total_index;

                    while (view_sizes[base_index] <= inner_index) {
                        inner_index -= view_sizes[base_index];
                        ++base_index;
                    }

                    index_map[total_index] = mapped_index{base_index, inner_index};
                }

                return index_map;
            }(indices_for<Base>);

            return meta::constant<result>;
        }

        static constexpr auto index_map_ = make_index_map();
        using index_map_t                = decltype(index_map_)::value_type;

        Base base_;

        template <typename Self>
        [[nodiscard]]
        constexpr decltype(auto) base(this Self&& self) noexcept {
            return std::forward_like<Self>(self.base_);
        }

        template <std::size_t Idx, typename Self>
        static consteval bool is_nothrow() {
            constexpr auto map         = index_map_[index<Idx>];
            constexpr auto base_index  = meta::constant_invoke(meta::constant<&mapped_index::base_index>, map);
            constexpr auto inner_index = meta::constant_invoke(meta::constant<&mapped_index::inner_index>, map);

            return noexcept(tuples::get(tuples::get(std::declval<Self>().base(), base_index), inner_index));
        }

    public:
        static constexpr auto size = meta::constant_invoke(meta::constant<&index_map_t::size>, index_map_);

        constexpr explicit flatten_view_base(Base base) noexcept :
            base_(std::move(base)) {}

        template <std::size_t Idx, typename Self>
        requires (Idx < size)
        [[nodiscard]]
        constexpr decltype(auto) get(this Self&& self) noexcept(is_nothrow<Idx, Self>()) {
            constexpr auto map         = index_map_[index<Idx>];
            constexpr auto base_index  = meta::constant_invoke(meta::constant<&mapped_index::base_index>, map);
            constexpr auto inner_index = meta::constant_invoke(meta::constant<&mapped_index::inner_index>, map);

            return tuples::get(tuples::get(self.base(), base_index), inner_index);
        }
};

} // namespace yu::tuples::_detail

#endif
