// yutool: include guard
#ifndef YU_TUPLES_CONCEPTS_TUPLE_HPP_
#define YU_TUPLES_CONCEPTS_TUPLE_HPP_

#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/access/size.hpp>

namespace yu::tuples {

namespace _detail::tuple {

template <typename T>
concept sized = requires { tuples::size<T>::value; };

template <typename T, std::size_t Idx>
concept gettable_at = requires(T&& t) { tuples::get(std::forward<T>(t), index<Idx>); };

template <typename T, std::size_t... Idx>
consteval bool all_gettable_impl(std::index_sequence<Idx...>) {
    return (gettable_at<T, Idx> && ...);
}

template <typename T>
consteval bool all_gettable() {
    return all_gettable_impl<T>(std::make_index_sequence<size_v<T>>{});
}

} // namespace _detail::tuple

template <typename T>
concept tuple = _detail::tuple::sized<std::remove_cvref_t<T>> && _detail::tuple::all_gettable<std::remove_cvref_t<T>>();

} // namespace yu::tuples

#endif
