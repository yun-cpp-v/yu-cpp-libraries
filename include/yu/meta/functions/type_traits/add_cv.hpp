// yutool: include guard
#ifndef YU_META_FUNCTIONS_TYPE_TRAITS_ADD_CV_HPP_
#define YU_META_FUNCTIONS_TYPE_TRAITS_ADD_CV_HPP_

#include "_detail/define_macros.hpp" // IWYU pragma: keep

namespace yu::meta::functions {

DEFINE_UNARY_TRAIT(add_cv, _t, type_t)

} // namespace yu::meta::functions

#include "_detail/undef_macros.hpp" // IWYU pragma: keep

#endif
