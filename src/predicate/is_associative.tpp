#ifndef _OMNI_REFLECTOR_PREDICATE_IS_ASSOCIATIVE_TPP_
#define _OMNI_REFLECTOR_PREDICATE_IS_ASSOCIATIVE_TPP_

#include <type_traits>

namespace omni::reflector::predicate {
    namespace _private {
        template <typename T, typename = void>
        struct _is_associative : std::false_type {};

        template <typename T>
        struct _is_associative<T, std::void_t<typename T::key_type>> : std::true_type {};
    }


    template <typename T>
    struct is_any_associative : _private::_is_associative<T> {

    };

    template <typename T>
    using is_associative = is_any_associative<T>;

    template <typename T>
    using is_not_associative = std::negation<is_any_associative<T>>;
}

#endif
