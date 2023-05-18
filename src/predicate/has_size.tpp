#ifndef _OMNI_REFLECTOR_PREDICATE_HAS_SIZE_TPP_
#define _OMNI_REFLECTOR_PREDICATE_HAS_SIZE_TPP_

#include <type_traits>

namespace omni::reflector::predicate {
    namespace _private {
        template <typename T>
        constexpr auto _has_size(int) -> decltype(std::declval<const T>().size(), std::true_type{});

        template <typename T>
        constexpr auto _has_size(...) -> std::false_type;
    }

    template <typename T>
    struct has_any_size : std::bool_constant<decltype(_private::_has_size<T>(0))::value> {

    };

    /**
     * Note that we assume that size SHOULD be const method
    */
    template <typename T>
    using has_size = has_any_size<T>;
}

#endif
