#ifndef _OMNI_REFLECTOR_REFLECTION_H_
#define _OMNI_REFLECTOR_REFLECTION_H_

#include "field.tpp"

namespace omni::reflector {
    template<class T>
    struct Reflection {

    };

}

#define OMNI_TYPE_NAME_INFO(_TYPE)                                                          \
    const constexpr static std::type_info &typeInfo = typeid(_TYPE);                        \
    const constexpr static auto clearTypeName = #_TYPE;                                     \

#define OMNI_TYPE_NAME_INFO_NAME(_NAMESPACE, _TYPE)                                         \
    const constexpr static std::type_info &typeInfo = typeid(_NAMESPACE::_TYPE);            \
    const constexpr static auto clearTypeName = #_TYPE;                                     \

#define OMNI_ADAPT_STRUCTURE_0(_TYPE)						                                \
template<>																	                \
struct omni::reflector::Reflection<_TYPE> {									                \
    OMNI_TYPE_NAME_INFO(_TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple();                                   \
};																			                \

#define OMNI_ADAPT_STRUCTURE_1(_TYPE, _field1)						                        \
template<>																	                \
struct omni::reflector::Reflection<_TYPE> {									                \
    OMNI_TYPE_NAME_INFO(_TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field1, #_field1)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_2(_TYPE, _field1, _field2)						                \
template<>																	                \
struct omni::reflector::Reflection<_TYPE> {									                \
    OMNI_TYPE_NAME_INFO(_TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field1, #_field1),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field2, #_field2)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_3(_TYPE, _field1, _field2, _field3)						    \
template<>																	                \
struct omni::reflector::Reflection<_TYPE> {									                \
    OMNI_TYPE_NAME_INFO(_TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field1, #_field1),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field2, #_field2),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field3, #_field3)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_4(_TYPE, _field1, _field2, _field3, _field4)					\
template<>																	                \
struct omni::reflector::Reflection<_TYPE> {									                \
    OMNI_TYPE_NAME_INFO(_TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field1, #_field1),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field2, #_field2),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field3, #_field3),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field4, #_field4)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_5(_TYPE, _field1, _field2, _field3, _field4, _field5)			\
template<>																	                \
struct omni::reflector::Reflection<_TYPE> {									                \
    OMNI_TYPE_NAME_INFO(_TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field1, #_field1),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field2, #_field2),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field3, #_field3),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field4, #_field4),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_TYPE::_field5, #_field5)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_0_NAME(_NAMESPACE, _TYPE)						                \
template<>																	                \
struct omni::reflector::Reflection<_NAMESPACE::_TYPE> {									                \
    OMNI_TYPE_NAME_INFO_NAME(_NAMESPACE, _TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple();                                   \
};																			                \

#define OMNI_ADAPT_STRUCTURE_1_NAME(_NAMESPACE, _TYPE, _field1)						        \
template<>																	                \
struct omni::reflector::Reflection<_NAMESPACE::_TYPE> {									                \
    OMNI_TYPE_NAME_INFO_NAME(_NAMESPACE, _TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field1, #_field1)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_2_NAME(_NAMESPACE, _TYPE, _field1, _field2)					\
template<>																	                \
struct omni::reflector::Reflection<_NAMESPACE::_TYPE> {									                \
    OMNI_TYPE_NAME_INFO_NAME(_NAMESPACE, _TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field1, #_field1),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field2, #_field2)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_3_NAME(_NAMESPACE, _TYPE, _field1, _field2, _field3)			\
template<>																	                \
struct omni::reflector::Reflection<_NAMESPACE::_TYPE> {									                \
    OMNI_TYPE_NAME_INFO_NAME(_NAMESPACE, _TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field1, #_field1),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field2, #_field2),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field3, #_field3)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_4_NAME(_NAMESPACE, _TYPE, _field1, _field2, _field3, _field4)	\
template<>																	                \
struct omni::reflector::Reflection<_NAMESPACE::_TYPE> {									                \
    OMNI_TYPE_NAME_INFO_NAME(_NAMESPACE, _TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field1, #_field1),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field2, #_field2),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field3, #_field3),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field4, #_field4)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE_5_NAME(_NAMESPACE, _TYPE, _field1, _field2, _field3, _field4, _field5)\
template<>																	                \
struct omni::reflector::Reflection<_NAMESPACE::_TYPE> {									                \
    OMNI_TYPE_NAME_INFO_NAME(_NAMESPACE, _TYPE)                                                              \
    const constexpr static auto meta = std::make_tuple(						                \
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field1, #_field1),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field2, #_field2),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field3, #_field3),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field4, #_field4),	\
        omni::reflector::FieldFriendlyScope::field_registration(&_NAMESPACE::_TYPE::_field5, #_field5)	\
    );																		                \
};																			                \

#define OMNI_ADAPT_STRUCTURE(...) OMNI_GET_MACRO(__VA_ARGS__, OMNI_ADAPT_STRUCTURE_5, OMNI_ADAPT_STRUCTURE_4, OMNI_ADAPT_STRUCTURE_3, OMNI_ADAPT_STRUCTURE_2, OMNI_ADAPT_STRUCTURE_1, OMNI_ADAPT_STRUCTURE_0)(__VA_ARGS__)
#define OMNI_GET_MACRO(_0, _1, _2, _3, _4, _5, NAME, ...) NAME

#define OMNI_ADAPT_STRUCTURE_NAME(...) OMNI_GET_MACRO_NAME(__VA_ARGS__, OMNI_ADAPT_STRUCTURE_5_NAME, OMNI_ADAPT_STRUCTURE_4_NAME, OMNI_ADAPT_STRUCTURE_3_NAME, OMNI_ADAPT_STRUCTURE_2_NAME, OMNI_ADAPT_STRUCTURE_1_NAME, OMNI_ADAPT_STRUCTURE_0_NAME)(__VA_ARGS__)
#define OMNI_GET_MACRO_NAME(_0, _1, _2, _3, _4, _5, _6, NAME, ...) NAME

#endif
