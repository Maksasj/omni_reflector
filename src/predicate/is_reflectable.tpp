#ifndef _OMNI_REFLECTOR_PREDICATE_IS_REFLECTABLE_H_
#define _OMNI_REFLECTOR_PREDICATE_IS_REFLECTABLE_H_

#include <type_traits>

namespace omni::reflector::predicate {
    template <class T>
    struct is_reflectable : std::is_base_of<Reflected<T>, T> {};
}

#endif
