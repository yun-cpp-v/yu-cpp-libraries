// yutool: include guard
#ifndef YU_TUPLES_CONCEPTS_TUPLE_HPP_
#define YU_TUPLES_CONCEPTS_TUPLE_HPP_

#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/access/size.hpp>
#include <tuple>
#include <type_traits>

namespace yu::tuples {

namespace _detail {

template <typename T>
concept sized = requires { size<T>::value; };

template <typename T, std::size_t Idx>
concept gettable_at = requires(T&& t) { tuples::get(std::forward<T>(t), index<Idx>); };

template <typename T, std::size_t... Idx>
consteval bool all_gettable_impl(std::index_sequence<Idx...>) {
    return (gettable_at<T, Idx> && ...);
}

template <typename T>
consteval bool all_gettable() {
    if constexpr (std::is_bounded_array_v<T>) {
        return all_gettable_impl<T>(std::make_index_sequence<std::extent_v<T>>{});
    } else if constexpr (tuple_size_defined<T>) {
        return all_gettable_impl<T>(std::make_index_sequence<std::tuple_size_v<T>>{});
    }

    return false;
}

} // namespace _detail

template <typename T>
concept tuple = _detail::sized<std::remove_cvref_t<T>> && _detail::all_gettable<std::remove_cvref_t<T>>();

} // namespace yu::tuples

#endif
