#ifndef _OMNI_REFLECTOR_FIELD_H_
#define _OMNI_REFLECTOR_FIELD_H_

#include <iostream>
#include <functional>

#include <type_traits>

#include "property.tpp"

namespace omni::reflector {
    template<typename Class, typename T>
    constexpr auto field_registration(T Class::*member, const char* name) {
        return PropertyImpl<Class, T>{member, name};
    }

    #define field(fieldName) field_registration(&Type::fieldName, #fieldName)

    template<template<typename PredicateMetaType> class Predicate, size_t Index = 0, class MetaObject, class Callable>
    constexpr void for_each_field(const MetaObject& obj, Callable&& lambda) noexcept {
        using metaType = decltype(obj.meta);

        if constexpr(Index == std::tuple_size<metaType>::value) {
            return;
        } else {
            auto fieldEntry = std::get<Index>(obj.meta);
            using FieldType = typename decltype(fieldEntry)::Type;

            auto& memberPtr = fieldEntry._member;
            auto& member = *reinterpret_cast<FieldType*>(&memberPtr);

            if constexpr (Predicate<FieldType>::value) {
                lambda(fieldEntry._name, obj.*(memberPtr));
            }

            for_each_field<Predicate, Index + 1>(obj, lambda);
        }
    }
}

#endif
