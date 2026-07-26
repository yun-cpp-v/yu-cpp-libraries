// yutool: include guard
#ifndef YU_TUPLES_ACCESS_SIZE_HPP_
#define YU_TUPLES_ACCESS_SIZE_HPP_

#include "index.hpp"
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace yu::tuples {

namespace _detail {

template <typename T>
concept tuple_size_defined = requires {
    typename std::tuple_size<T>;
    std::tuple_size<T>::value;
};

template <typename T>
consteval std::size_t size_impl() {
    if constexpr (std::is_bounded_array_v<T>) {
        return std::extent_v<T>;
    } else if constexpr (tuple_size_defined<T>) {
        return std::tuple_size_v<T>;
    }
}

} // namespace _detail

template <typename T>
struct size {};

template <typename T>
requires std::is_bounded_array_v<std::remove_cvref_t<T>> || _detail::tuple_size_defined<std::remove_cvref_t<T>>
struct size<T> : index_t<_detail::size_impl<std::remove_cvref_t<T>>()> {};

template <typename T>
inline constexpr std::size_t size_v = size<T>::value;

} // namespace yu::tuples

#endif
