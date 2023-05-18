#ifndef _OMNI_REFLECTOR_PREDICATE_IS_ANY_TPP_
#define _OMNI_REFLECTOR_PREDICATE_IS_ANY_TPP_

#include <type_traits>

namespace omni::reflector::predicate {
    template <class T>
    struct is_any : std::bool_constant<true> {
        
    };
}

#endif
