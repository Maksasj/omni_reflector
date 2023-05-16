#ifndef _OMNI_REFLECTOR_PROPERTY_H_
#define _OMNI_REFLECTOR_PROPERTY_H_

namespace omni::reflector {
    template<typename Class, typename T>
    struct PropertyImpl {
        constexpr PropertyImpl(T Class::*member, const char* name) 
            : _member{member}, _name{name} {

        }

        using Type = T;

        Type Class::* _member;
        const char* _name;
    };
}

#endif