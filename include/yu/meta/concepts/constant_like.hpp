// yutool: include guard
#ifndef YU_META_CONCEPTS_CONSTANT_LIKE_HPP_
#define YU_META_CONCEPTS_CONSTANT_LIKE_HPP_

#include <concepts>
#include <type_traits>

namespace yu::meta {

template <auto Value>
struct constant_t;

template <typename C>
concept constant_like = requires { constant_t<std::remove_cvref_t<C>::value>{}; };

template <typename C, typename T>
concept constant_like_of = constant_like<C> && requires {
    { auto(std::remove_cvref_t<C>::value) } -> std::same_as<T>;
};

} // namespace yu::meta

#endif
