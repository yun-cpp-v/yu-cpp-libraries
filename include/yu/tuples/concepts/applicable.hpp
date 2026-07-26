// yutool: include guard
#ifndef YU_TUPLES_CONCEPTS_APPLICABLE_HPP_
#define YU_TUPLES_CONCEPTS_APPLICABLE_HPP_

#include <yu/tuples/apply.hpp>

namespace yu::tuples {

template <typename F, typename Tup>
concept applicable = requires(F&& fn, Tup&& t) { tuples::apply(std::forward<F>(fn), std::forward<Tup>(t)); };

template <typename F, typename Tup>
concept regular_applicable = applicable<F, Tup>;

} // namespace yu::tuples

#endif
