#ifndef _OMNI_REFLECTOR_FIELD_H_
#define _OMNI_REFLECTOR_FIELD_H_

#include <iostream>
#include <functional>

#include "property.tpp"

namespace omni::reflector {
    template<typename Class, typename T>
    constexpr auto field_registration(T Class::*member, const char* name) {
        return PropertyImpl<Class, T>{member, name};
    }

    #define field(fieldName) field_registration(&Type::fieldName, #fieldName)

    template<size_t I = 0, class Object, typename... Ts, class Callable>
    constexpr void for_each_field(const Object& obj, std::tuple<Ts...> tup, Callable&& lambda) {
        if constexpr(I == sizeof...(Ts)) {
            return;
        } else {
            auto fieldEntry = std::get<I>(tup);
            using FieldType = typename decltype(fieldEntry)::Type;

            auto& memberPtr = fieldEntry._member;
            auto& member = *reinterpret_cast<FieldType*>(&memberPtr);

            if constexpr (!std::is_base_of<Reflected<FieldType>, FieldType>::value) {
                lambda(fieldEntry._name, obj.*(memberPtr));
            }


            for_each_field<I + 1>(obj, tup, lambda);
        }
    }

    template<size_t I = 0, class Object, typename... Ts, class Callable>
    constexpr void for_each_reflectable_field(const Object& obj, std::tuple<Ts...> tup, Callable&& lambda) {
        if constexpr(I == sizeof...(Ts)) {
            return;
        } else {
            auto fieldEntry = std::get<I>(tup);
            using FieldType = typename decltype(fieldEntry)::Type;

            auto& memberPtr = fieldEntry._member;
            auto& member = *reinterpret_cast<FieldType*>(&memberPtr);

            if constexpr (std::is_base_of<Reflected<FieldType>, FieldType>::value) {
                lambda(fieldEntry._name, obj.*(memberPtr));
            }

            for_each_reflectable_field<I + 1>(obj, tup, lambda);
        }
    }

    /*
    template<size_t I = 0, class Object, typename... Ts, class Callable>
    constexpr void for_each_field_recursive(const Object& obj, std::tuple<Ts...> tup, Callable&& lambda) {
        for_each_field(obj, tup, [&](const char* fieldName, auto& fieldEntry) {
            using FieldType = typename decltype(fieldEntry)::Type;

            if constexpr (std::is_base_of<Reflected<FieldType>, FieldType>::value) {
                auto& memberPtr = fieldEntry._member;
                auto& member = *reinterpret_cast<FieldType*>(&memberPtr);

                //for_each_field_recursive(obj, member.meta, lambda);
            } else {
                //lambda(fieldEntry);
            }
        });
    }
    */
}

#endif