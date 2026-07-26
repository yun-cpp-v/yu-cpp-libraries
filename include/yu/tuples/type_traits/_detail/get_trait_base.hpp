// yutool: include guard
#ifndef YU_TUPLES_TYPE_TRAITS_DETAIL_GET_TRAIT_BASE_HPP_
#define YU_TUPLES_TYPE_TRAITS_DETAIL_GET_TRAIT_BASE_HPP_

#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <yu/tuples/concepts/tuple.hpp>
#include <cstddef>

namespace yu::tuples::_detail {

struct default_fallback {};

template <
    template <typename...> typename InvocationTrait,
    std::size_t Idx,
    typename T,
    typename Fallback = default_fallback
>
struct get_trait_base : Fallback {};

template <template <typename...> typename InvocationTrait, std::size_t Idx, typename Tuple, typename Fallback>
requires tuple<Tuple> && (Idx < size_v<Tuple>)
struct get_trait_base<InvocationTrait, Idx, Tuple, Fallback> :
    InvocationTrait<decltype(tuples::get), Tuple, index_t<Idx>> {};

} // namespace yu::tuples::_detail

#endif
