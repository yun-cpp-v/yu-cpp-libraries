#include <concepts>

template <typename T>
concept member_type_defined = requires { typename T::type; };

template <typename T>
concept member_value_defined = requires { T::value; };

template <typename T, typename U>
concept member_value_defined_as = requires {
    { auto(T::value) } -> std::same_as<U>;
};
