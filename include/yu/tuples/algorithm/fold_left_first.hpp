// yutool: include guard
#ifndef YU_TUPLES_ALGORITHM_FOLD_LEFT_FIRST_HPP_
#define YU_TUPLES_ALGORITHM_FOLD_LEFT_FIRST_HPP_

#include "_detail/fold_left_impl.hpp"
#include "_detail/left_fold_concepts.hpp"
#include <yu/tuples/apply.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <utility>

namespace yu::tuples {

namespace _unspecified {

struct fold_left_first_fn {
    public:
        template <tuple Tuple, typename Fn>
        requires _detail::left_foldable_first<Fn, Tuple>
        [[nodiscard]]
        static constexpr auto operator()(Tuple&& tuple, Fn f) {
            return tuples::apply(
                [&]<typename... Elems>(Elems&&... elems) {
                    return _detail::fold_left_impl(f, std::forward<Elems>(elems)...);
                },
                std::forward<Tuple>(tuple)
            );
        }
};

} // namespace _unspecified

inline namespace _fn {

inline constexpr _unspecified::fold_left_first_fn fold_left_first{};

}

} // namespace yu::tuples

#endif
