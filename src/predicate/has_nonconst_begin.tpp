#ifndef _OMNI_REFLECTOR_PREDICATE_HAS_NONCONST_BEGIN_H_
#define _OMNI_REFLECTOR_PREDICATE_HAS_NONCONST_BEGIN_H_

#include <type_traits>

namespace omni::reflector::predicate {
    namespace _private {
        template <typename T>
        constexpr auto _has_nonconst_begin(int) -> decltype(std::declval<T>().begin(), std::true_type{});

        template <typename T>
        constexpr auto _has_nonconst_begin(...) -> std::false_type;
    }

    template <typename T>
    struct has_nonconst_begin : std::bool_constant<decltype(_private::_has_nonconst_begin<T>(0))::value> {

    };
}

#endif
