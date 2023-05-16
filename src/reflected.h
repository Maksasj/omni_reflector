#ifndef _OMNI_REFLECTOR_REFLECTED_H_
#define _OMNI_REFLECTOR_REFLECTED_H_

namespace omni::reflector {
    template<class T>
    struct Reflected {
        using Type = T;
    };
}

#endif