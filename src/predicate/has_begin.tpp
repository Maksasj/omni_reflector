#ifndef _OMNI_REFLECTOR_PREDICATE_HAS_BEGIN_TPP_
#define _OMNI_REFLECTOR_PREDICATE_HAS_BEGIN_TPP_

#include <type_traits>

namespace omni::reflector::predicate {
    namespace _private {
        template <typename T>
        constexpr auto _has_nonconst_begin(int) -> decltype(std::declval<T>().begin(), std::true_type{});

        template <typename T>
        constexpr auto _has_nonconst_begin(...) -> std::false_type;

        template <typename T>
        constexpr auto _has_const_begin(int) -> decltype(std::declval<const T>().begin(), std::true_type{});

        template <typename T>
        constexpr auto _has_const_begin(...) -> std::false_type;
    }

    template <typename T>
    struct has_nonconst_begin : std::bool_constant<decltype(_private::_has_nonconst_begin<T>(0))::value> {

    };

    template <typename T>
    struct has_const_begin : std::bool_constant<decltype(_private::_has_const_begin<T>(0))::value> {

    };

    template <typename T>
    struct has_all_begin : std::bool_constant<std::conjunction<has_nonconst_begin<T>, has_const_begin<T>>::value> {

    };

    template <typename T>
    struct has_any_begin : std::bool_constant<std::disjunction<has_nonconst_begin<T>, has_const_begin<T>>::value> {

    };

    template <typename T>
    using has_begin = has_any_begin<T>;
}

#endif
