#ifndef _OMNI_REFLECTOR_PREDICATE_HAS_END_TPP_
#define _OMNI_REFLECTOR_PREDICATE_HAS_END_TPP_

#include <type_traits>

namespace omni::reflector::predicate {
    namespace _private {
        template <typename T>
        constexpr auto _has_nonconst_end(int) -> decltype(std::declval<T>().end(), std::true_type{});

        template <typename T>
        constexpr auto _has_nonconst_end(...) -> std::false_type;

        template <typename T>
        constexpr auto _has_const_end(int) -> decltype(std::declval<const T>().end(), std::true_type{});

        template <typename T>
        constexpr auto _has_const_end(...) -> std::false_type;
    }

    template <typename T>
    struct has_nonconst_end : std::bool_constant<decltype(_private::_has_nonconst_end<T>(0))::value> {

    };

    template <typename T>
    struct has_const_end : std::bool_constant<decltype(_private::_has_const_end<T>(0))::value> {

    };

    template <typename T>
    struct has_all_end : std::bool_constant<std::conjunction<has_nonconst_end<T>, has_const_end<T>>::value> {

    };

    template <typename T>
    struct has_any_end : std::bool_constant<std::disjunction<has_nonconst_end<T>, has_const_end<T>>::value> {

    };

    template <typename T>
    using has_end = has_any_end<T>;
}

#endif
