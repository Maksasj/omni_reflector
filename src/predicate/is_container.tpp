#ifndef _OMNI_REFLECTOR_PREDICATE_IS_CONTAINER_TPP_
#define _OMNI_REFLECTOR_PREDICATE_IS_CONTAINER_TPP_

#include <type_traits>

#include "has_begin.tpp"
#include "has_end.tpp"

namespace omni::reflector::predicate {
    template <typename T>
    using is_container = std::conjunction<has_begin<T>, has_end<T>>;
    
    template <typename T>
    using is_not_container = std::negation<is_container<T>>;
}

#endif
