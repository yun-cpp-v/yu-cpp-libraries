// yutool: include guard
#ifndef YU_META_FUNCTIONS_TYPE_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP_
#define YU_META_FUNCTIONS_TYPE_TRAITS_IS_MOVE_CONSTRUCTIBLE_HPP_

#include "_detail/define_macros.hpp" // IWYU pragma: keep

namespace yu::meta::functions {

DEFINE_UNARY_TRAIT(is_move_constructible, _v, constant_t)

} // namespace yu::meta::functions

#include "_detail/undef_macros.hpp" // IWYU pragma: keep

#endif
