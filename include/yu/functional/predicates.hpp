// yutool: include guard
#ifndef YU_FUNCTIONAL_PREDICATES_HPP_
#define YU_FUNCTIONAL_PREDICATES_HPP_

#include "with_fallback.hpp"
#include <functional>

namespace yu::functional {

using safe_equal_to = with_fallback_t<std::ranges::equal_to, bool>;

} // namespace yu::functional

#endif
