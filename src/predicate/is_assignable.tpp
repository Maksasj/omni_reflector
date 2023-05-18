#ifndef _OMNI_REFLECTOR_PREDICATE_IS_ASSIGNABLE_TPP_
#define _OMNI_REFLECTOR_PREDICATE_IS_ASSIGNABLE_TPP_

#include <type_traits>

namespace omni::reflector::predicate {
    template <class To, class From>
    struct is_assignable : std::bool_constant<std::is_constructible<To, From>::value> {

    };

    template <class To, class From>
    struct is_not_assignable : std::negation<is_assignable<To, From>> {
        
    };
}

#endif
