#ifndef _OMNI_REFLECTOR_FIELD_IMPLEMENTATION_TPP_
#define _OMNI_REFLECTOR_FIELD_IMPLEMENTATION_TPP_

namespace omni::reflector {
    template<typename Class, typename T>
    struct FieldImpl {
        constexpr FieldImpl(T Class::*member, const char* name) 
            : _member{member}, _name{name} {

        }

        using Type = T;

        Type Class::* _member;
        const char* _name;
    };
}

#endif