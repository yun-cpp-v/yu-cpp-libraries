// yutool: include guard
#ifndef YU_TUPLES_ACCESS_GET_HPP_
#define YU_TUPLES_ACCESS_GET_HPP_

#include "index.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>

namespace yu::tuples {

namespace _detail {

// Poison Pill
template <std::size_t>
void get() = delete;

template <std::size_t Idx, typename T>
concept member_gettable = requires(T&& t) { std::forward<T>(t).template get<Idx>(); };

template <std::size_t Idx, typename T>
concept unqualified_gettable = requires(T&& t) { get<Idx>(std::forward<T>(t)); };

} // namespace _detail

namespace _unspecified {

struct get_fn {
    private:
        template <std::size_t Idx, typename T>
        [[nodiscard]]
        static constexpr bool is_nothrow(T&& t, index_t<Idx>) {
            if constexpr (std::is_bounded_array_v<std::remove_cvref_t<T>>) {
                return true;
            } else if constexpr (_detail::member_gettable<Idx, T>) {
                return noexcept(std::forward<T>(t).template get<Idx>());
            } else {
                using _detail::get;

                return noexcept(get<Idx>(std::forward<T>(t)));
            }
        }

    public:
        template <std::size_t Idx, typename T>
        [[nodiscard]]
        static constexpr decltype(auto) operator()(T&& t, index_t<Idx> index) noexcept(
            is_nothrow(std::forward<T>(t), index)
        ) {
            if constexpr (std::is_bounded_array_v<std::remove_cvref_t<T>>) {
                return std::forward<T>(t)[Idx];
            } else if constexpr (_detail::member_gettable<Idx, T>) {
                return std::forward<T>(t).template get<Idx>();
            } else {
                using _detail::get;

                return get<Idx>(std::forward<T>(t));
            }
        }
};

} // namespace _unspecified

inline namespace _cpo {

inline constexpr _unspecified::get_fn get{};

}

} // namespace yu::tuples

#endif
