// yutool: include guard
#ifndef YU_TUPLES_CONSTRUCT_CONSTRUCT_HPP_
#define YU_TUPLES_CONSTRUCT_CONSTRUCT_HPP_

#include <yu/tuples/apply.hpp>
#include <yu/tuples/concepts/constructible_from_elements.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <yu/tuples/concepts/view.hpp>

namespace yu::tuples {

namespace _detail {

template <template <typename...> typename RetT, typename Tuple, typename... Args>
struct deduce_from_elements {
    private:
        template <std::size_t... Idx>
        static consteval auto deduce(std::index_sequence<Idx...>)
            -> decltype(RetT{std::declval<element_type_t<Idx, Tuple>>()..., std::declval<Args>()...});

    public:
        using type = std::remove_cvref_t<decltype(deduce(indices_for<Tuple>))>;
};

template <template <typename...> typename Ret, typename Tuple, typename... Args>
using deduce_from_elements_t = deduce_from_elements<Ret, Tuple, Args...>::type;

template <typename Ret, typename Tuple, typename... Args>
constexpr Ret construct_impl(Tuple&& tuple, Args&&... args) {
    return tuples::apply(
        [&]<typename... Elems>(Elems&&... elems) {
            return Ret{std::forward<Elems>(elems)..., std::forward<Args>(args)...};
        },
        std::forward<Tuple>(tuple)
    );
}

} // namespace _detail

template <typename Ret, tuple Tuple, typename... Args>
requires constructible_from_elements<Ret, Tuple, Args...> && (!view<Ret>)
[[nodiscard]]
constexpr Ret construct(Tuple&& tuple, Args&&... args) {
    return _detail::construct_impl<Ret>(std::forward<Tuple>(tuple), std::forward<Args>(args)...);
}

template <template <typename...> typename RetT, tuple Tuple, typename... Args>
[[nodiscard]]
constexpr decltype(auto) construct(Tuple&& tuple, Args&&... args) {
    return _detail::construct_impl<_detail::deduce_from_elements_t<RetT, Tuple, Args...>>(
        std::forward<Tuple>(tuple),
        std::forward<Args>(args)...
    );
}

namespace _unspecified {

template <typename Ret, typename... Args>
class construct_type_adaptor {
    private:
        std::tuple<Args...> args_;

    public:
        constexpr explicit construct_type_adaptor(Args... args) :
            args_(std::move(args)...) {}

        template <tuple Tuple, typename Adaptor>
        requires std::same_as<std::remove_cvref_t<Adaptor>, construct_type_adaptor<Ret, Args...>>
        [[nodiscard]]
        friend constexpr auto operator|(Tuple&& tuple, Adaptor&& adaptor) {
            return tuples::apply(
                [&]<typename... Elems>(Elems&&... elems) {
                    return construct<Ret>(std::forward<Tuple>(tuple), std::forward<Elems>(elems)...);
                },
                std::forward_like<Adaptor>(adaptor.args_)
            );
        }
};

template <template <typename...> typename RetT, typename... Args>
class construct_template_adaptor {
    private:
        std::tuple<Args...> args_;

    public:
        constexpr explicit construct_template_adaptor(Args... args) :
            args_(std::move(args)...) {}

        template <tuple Tuple, typename Adaptor>
        requires std::same_as<std::remove_cvref_t<Adaptor>, construct_template_adaptor<RetT, Args...>>
        [[nodiscard]]
        friend constexpr auto operator|(Tuple&& tuple, Adaptor&& adaptor) {
            return tuples::apply(
                [&]<typename... Elems>(Elems&&... elems) {
                    return construct<RetT>(std::forward<Tuple>(tuple), std::forward<Elems>(elems)...);
                },
                std::forward_like<Adaptor>(adaptor.args_)
            );
        }
};

} // namespace _unspecified

template <typename Ret, typename... Args>
[[nodiscard]]
constexpr auto construct(Args&&... args) noexcept {
    return _unspecified::construct_type_adaptor<Ret, std::decay_t<Args>...>{std::forward<Args>(args)...};
}

template <template <typename...> typename RetT, typename... Args>
[[nodiscard]]
constexpr auto construct(Args&&... args) noexcept {
    return _unspecified::construct_template_adaptor<RetT, std::decay_t<Args>...>{std::forward<Args>(args)...};
}

} // namespace yu::tuples

#endif
