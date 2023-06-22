#ifndef _OMNI_REFLECTOR_FIELD_TPP_
#define _OMNI_REFLECTOR_FIELD_TPP_

#include <iostream>
#include <functional>

#include <type_traits>

#include "field_implementation.tpp"

namespace omni::reflector {
    struct FieldFriendlyScope {
        template<typename Class, typename T>
        static constexpr auto field_registration(T Class::*member, const char* name) noexcept {
            return FieldImpl<Class, T>{member, name};
        }

        template<template<typename PredicateMetaType> class Predicate, size_t Index = 0, class MetaObject, class Callable>
        static constexpr void for_each_field(MetaObject& obj, Callable&& lambda) noexcept {
            using metaType = decltype(obj.meta);

            if constexpr(Index == std::tuple_size<metaType>::value) {
                return;
            } else {
                auto fieldEntry = std::get<Index>(obj.meta);
                using FieldType = typename decltype(fieldEntry)::Type;

                auto& memberPtr = fieldEntry._member;

                if constexpr (Predicate<FieldType>::value)
                    lambda(fieldEntry._name, obj.*(memberPtr));

                for_each_field<Predicate, Index + 1>(obj, lambda);
            }
        }
    };

    #define field(fieldName) FieldFriendlyScope::field_registration(&Type::fieldName, #fieldName)
}

#endif
