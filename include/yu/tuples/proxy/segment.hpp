// yutool: include guard
#ifndef YU_TUPLES_PROXY_SEGMENT_HPP_
#define YU_TUPLES_PROXY_SEGMENT_HPP_

#include "location.hpp"
#include <yu/tuples/utility/index_sequence_for.hpp>
#include <yu/tuples/views/all.hpp>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <ranges>
#include <utility>

namespace yu::tuples {

template <view View>
class segment_iterator {
    private:
        const View*    view_;
        std::size_t    first_;
        std::ptrdiff_t pos_;

    public:
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;

        using difference_type = std::ptrdiff_t;

        using value_type = location<View>;
        using reference  = value_type;
        using pointer    = void;

        constexpr segment_iterator()                                    = default;
        constexpr segment_iterator(View&&, std::size_t, std::ptrdiff_t) = delete;

        constexpr explicit segment_iterator(const View& view, std::size_t first, std::ptrdiff_t pos) noexcept :
            view_(std::addressof(view)), first_(first), pos_(pos) {}

        [[nodiscard]]
        constexpr value_type operator*() const noexcept {
            auto idx = static_cast<std::size_t>(static_cast<std::ptrdiff_t>(first_) + pos_);

            return value_type{*view_, idx};
        }

        [[nodiscard]]
        constexpr value_type operator[](difference_type n) const noexcept {
            return *(*this + n);
        }

        constexpr segment_iterator& operator++() noexcept {
            ++pos_;
            return *this;
        }

        constexpr segment_iterator operator++(int) noexcept {
            auto t = *this;
            ++*this;
            return t;
        }

        constexpr segment_iterator& operator--() noexcept {
            --pos_;
            return *this;
        }

        constexpr segment_iterator operator--(int) noexcept {
            auto t = *this;
            --*this;
            return t;
        }

        constexpr segment_iterator& operator+=(difference_type n) noexcept {
            pos_ += n;
            return *this;
        }

        constexpr segment_iterator& operator-=(difference_type n) noexcept {
            pos_ -= n;
            return *this;
        }

        [[nodiscard]]
        friend constexpr segment_iterator operator+(segment_iterator it, difference_type n) noexcept {
            return it += n;
        }

        [[nodiscard]]
        friend constexpr segment_iterator operator+(difference_type n, segment_iterator it) noexcept {
            return it += n;
        }

        [[nodiscard]]
        friend constexpr segment_iterator operator-(segment_iterator it, difference_type n) noexcept {
            return it -= n;
        }

        [[nodiscard]]
        friend constexpr difference_type operator-(segment_iterator a, segment_iterator b) noexcept {
            return a.pos_ - b.pos_;
        }

        [[nodiscard]]
        friend constexpr auto operator<=>(const segment_iterator& left, const segment_iterator& right) noexcept
            = default;
};

template <view View>
class segment : public std::ranges::view_interface<segment<View>> {
    private:
        View        view_;
        std::size_t first_, size_;

    public:
        using iterator        = segment_iterator<View>;
        using const_iterator  = iterator;
        using difference_type = std::ptrdiff_t;
        using size_type       = std::size_t;

        using value_type = iterator::value_type;
        using reference  = iterator::reference;

        constexpr explicit segment(View view, std::size_t first, std::size_t size) :
            view_(std::move(view)), first_(first), size_(size) {
            assert(first <= size_v<View>);
            assert(size <= size_v<View> - first);
        }

        template <typename Self>
        [[nodiscard]]
        constexpr decltype(auto) base(this Self&& self) noexcept {
            return std::forward_like<Self>(self.view_);
        }

        [[nodiscard]]
        constexpr std::size_t size() const noexcept {
            return size_;
        }

        [[nodiscard]]
        constexpr difference_type ssize() const noexcept {
            return static_cast<difference_type>(size_);
        }

        [[nodiscard]]
        constexpr iterator begin() const noexcept {
            return iterator{base(), first_, 0};
        }

        [[nodiscard]]
        constexpr iterator end() const noexcept {
            return iterator{base(), first_, this->ssize()};
        }

        [[nodiscard]]
        friend bool operator==(const segment&, const segment&) noexcept = default;
};

template <typename Tuple>
segment(Tuple&&, std::size_t, std::size_t) -> segment<views::all_t<Tuple&&>>;

} // namespace yu::tuples

#endif
