#ifndef _OMNI_REFLECTOR_PREDICATE_IS_REFLECTABLE_TPP_
#define _OMNI_REFLECTOR_PREDICATE_IS_REFLECTABLE_TPP_

#include <type_traits>

namespace omni::reflector::predicate {
    template <class T>
    struct is_reflectable : std::is_base_of<Reflected<T>, T> {};

    template <class T>
    struct is_not_reflectable : std::negation<is_reflectable<T>> { };
}

#endif
