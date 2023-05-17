#ifndef _OMNI_REFLECTOR_PREDICATE_ALL_CONST_BEGIN_H_
#define _OMNI_REFLECTOR_PREDICATE_ALL_CONST_BEGIN_H_

#include "has_const_begin.tpp"
#include "has_nonconst_begin.tpp"

namespace omni::reflector::predicate {
    template <typename T>
    struct has_all_begin : std::bool_constant<std::conjunction<has_nonconst_begin<T>, has_const_begin<T>>::value> {

    };
}

#endif
