// yutool: include guard
#ifndef YU_TUPLES_PROJECTED_HPP_
#define YU_TUPLES_PROJECTED_HPP_

#include "concepts/elementwise_unary_invocable.hpp"
#include "concepts/tuple.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>

namespace yu::tuples {

template <tuple Tuple, elementwise_unary_invocable<Tuple> Proj>
struct projected {
        // Declaration only
        template <std::size_t Idx>
        constexpr std::invoke_result_t<Proj, element_type_t<Idx, Tuple>> get() noexcept;
};

} // namespace yu::tuples

namespace std {

template <yu::tuples::tuple T, yu::tuples::elementwise_unary_invocable<T> Proj>
struct tuple_size<yu::tuples::projected<T, Proj>> : yu::tuples::size<T> {};

} // namespace std

#endif
