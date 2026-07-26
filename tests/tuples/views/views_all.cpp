#include <yu/tuples/views/all.hpp>
#include <yu/tuples/views/owning_view.hpp>
#include <yu/tuples/views/ref_view.hpp>
#include <concepts>
#include <tuple>

int main() {
    using namespace yu::tuples;

    auto tup = std::tuple{1, 3.14, 2};

    static_assert(std::same_as<decltype(views::all(tup)), decltype(ref_view{tup})>);
    static_assert(std::same_as<decltype(views::all(std::move(tup))), decltype(owning_view{std::move(tup)})>);
    static_assert(std::same_as<decltype(views::all(ref_view{tup})), decltype(ref_view{tup})>);
}