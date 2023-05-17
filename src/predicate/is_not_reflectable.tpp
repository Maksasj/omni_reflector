#ifndef _OMNI_REFLECTOR_PREDICATE_IS_NOT_REFLECTABLE_H_
#define _OMNI_REFLECTOR_PREDICATE_IS_NOT_REFLECTABLE_H_

#include <type_traits>

#include "is_reflectable.tpp"

namespace omni::reflector::predicate {
    template <class T>
    struct is_not_reflectable : std::negation<is_reflectable<T>> { };
}

#endif
