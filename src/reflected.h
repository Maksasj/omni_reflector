#ifndef _OMNI_REFLECTOR_REFLECTED_H_
#define _OMNI_REFLECTOR_REFLECTED_H_

template<typename T>
static char* get_type_name() {
	char *ename, *name = (char*) typeid(T).name(); 
	ename = name;

	while(*ename != '\0' && *ename != ':')
		++ename;

    return (*ename == ':') ? ename + 2 : name;
}

namespace omni::reflector {
    template<class T>
    struct Reflected {
        using Type = T;

        static const char* clearTypeName;
    };
    
    template<class T>
    const char* Reflected<T>::clearTypeName = get_type_name<T>();
}

#endif
