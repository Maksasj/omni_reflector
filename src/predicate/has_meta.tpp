#ifndef _OMNI_REFLECTOR_PREDICATE_HAS_META_TPP_
#define _OMNI_REFLECTOR_PREDICATE_HAS_META_TPP_

#include <type_traits>

namespace omni::reflector::predicate {
    namespace _private {
        template <typename T>
        constexpr auto _has_meta(int) -> decltype(std::declval<const T>().meta, std::true_type{});

        template <typename T>
        constexpr auto _has_meta(...) -> std::false_type;
    }

    template <typename T>
    struct has_any_meta : std::bool_constant<decltype(_private::_has_meta<T>(0))::value> {

    };

    template <typename T>
    using has_meta = has_any_meta<T>;
}

#endif
