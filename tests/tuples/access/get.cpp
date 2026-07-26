#include <yu/tuples/access/get.hpp>
#include <yu/tuples/access/index.hpp>
#include <concepts>
#include <cstddef>
#include <tuple>

template <bool NoExcept = true>
struct member_only {
        template <std::size_t Idx>
        constexpr auto get() const noexcept(NoExcept) {
            return 2 * Idx;
        }
};

template <bool NoExcept = true>
struct adl_only {
        template <std::size_t Idx>
        friend constexpr auto get(adl_only) noexcept(NoExcept) {
            return 2 * Idx + 1;
        }
};


int main() {
    using namespace yu::tuples;

    {
        constexpr int         raw_array[3] = {1, 2, 3};
        constexpr member_only member_only{};
        constexpr adl_only    adl_only{};

        static_assert(get(raw_array, index<0>) == 1);
        static_assert(get(raw_array, index<1>) == 2);
        static_assert(get(raw_array, index<2>) == 3);

        static_assert(get(member_only, index<0>) == 0);
        static_assert(get(member_only, index<1>) == 2);
        static_assert(get(member_only, index<2>) == 4);

        static_assert(get(adl_only, index<0>) == 1);
        static_assert(get(adl_only, index<1>) == 3);
        static_assert(get(adl_only, index<2>) == 5);
    }

    {
        constexpr member_only<true> member_only_noexcept{};
        constexpr adl_only<true>    adl_only_noexcept{};

        static_assert(noexcept(get(member_only_noexcept, index<0>)));
        static_assert(noexcept(get(adl_only_noexcept, index<0>)));

        constexpr member_only<false> member_only_throw{};
        constexpr adl_only<false>    adl_only_throw{};

        static_assert(!noexcept(get(member_only_throw, index<0>)));
        static_assert(!noexcept(get(adl_only_throw, index<0>)));
    }

    {
        int       raw_array[3]       = {1, 2, 3};
        const int const_raw_array[3] = {1, 2, 3};

        using get_t      = decltype(get(raw_array, index<0>));
        using move_get_t = decltype(get(std::move(raw_array), index<0>));

        static_assert(std::same_as<get_t, int&>);
        static_assert(std::same_as<move_get_t, int&&>);

        using const_get_t      = decltype(get(const_raw_array, index<0>));
        using const_move_get_t = decltype(get(std::move(const_raw_array), index<0>));

        static_assert(std::same_as<const_get_t, const int&>);
        static_assert(std::same_as<const_move_get_t, const int&&>);
    }

    {
        std::tuple       tuple{0, 1};
        const std::tuple const_tuple{0, 1};

        using get_t      = decltype(get(tuple, index<0>));
        using move_get_t = decltype(get(std::move(tuple), index<0>));

        static_assert(std::same_as<get_t, int&>);
        static_assert(std::same_as<move_get_t, int&&>);

        using const_get_t      = decltype(get(const_tuple, index<0>));
        using const_move_get_t = decltype(get(std::move(const_tuple), index<0>));

        static_assert(std::same_as<const_get_t, const int&>);
        static_assert(std::same_as<const_move_get_t, const int&&>);
    }

    {
        constexpr bool f = [] {
            int arr[2]{0, 1};
            get(arr, index<0>) = 2;

            std::tuple tuple{0, 1};
            get(tuple, index<0>) = 2;

            return arr[0] == 2 && std::get<0>(tuple) == 2;
        }();

        static_assert(f);
    }
}
