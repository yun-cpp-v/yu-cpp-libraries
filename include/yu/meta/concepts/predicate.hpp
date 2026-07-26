// yutool: include guard
#ifndef YU_META_CONCEPTS_PREDICATE_HPP_
#define YU_META_CONCEPTS_PREDICATE_HPP_

#include "constant_like.hpp"
#include <functional>

namespace yu::meta {

template <typename P, typename... Ts>
concept predicate = std::predicate<P, Ts...> && requires(P p, Ts... types) {
    { auto(std::invoke(p, types...)) } -> constant_like_of<bool>;
};

} // namespace yu::meta

#endif
