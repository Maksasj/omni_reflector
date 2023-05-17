#ifndef _OMNI_REFLECTOR_PREDICATE_HAS_CONST_BEGIN_H_
#define _OMNI_REFLECTOR_PREDICATE_HAS_CONST_BEGIN_H_

#include <type_traits>

namespace omni::reflector::predicate {
    namespace _private {
        template <typename T>
        constexpr auto _has_const_begin(int) -> decltype(std::declval<const T>().begin(), std::true_type{});

        template <typename T>
        constexpr auto _has_const_begin(...) -> std::false_type;
    }

    template <typename T>
    struct has_const_begin : std::bool_constant<decltype(_private::_has_const_begin<T>(0))::value> {

    };
}

#endif
