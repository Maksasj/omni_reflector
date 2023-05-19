#ifndef _OMNI_REFLECTOR_JSON_SERIALIZE_H_
#define _OMNI_REFLECTOR_JSON_SERIALIZE_H_

#include <nlohmann/json.hpp>

#include "predicates.h"
#include "reflected.h"

namespace omni::reflector::serialization {
    template<class Type> 
    nlohmann::json json_serialize(const Type& data) {
        using json = nlohmann::json;

        json object = json({});

        for_each_field<predicate::is_any>(data, [&](const char* fieldName, auto& field) {
            using fieldType = typename std::remove_const_t<std::remove_reference_t<decltype(field)>>;
            
            if constexpr (predicate::is_assignable<json, fieldType>::value) {
                object[fieldName] = field;
                return;
            }
            
            if constexpr (predicate::is_reflectable<fieldType>::value) {
                json inner = json_serialize(field);
                object[fieldName] = inner;
                return;
            }

            if constexpr (predicate::has_any_begin<fieldType>::value && predicate::has_any_end<fieldType>::value && predicate::is_not_assignable<json, fieldType>::value) {
                auto iterBegin = field.begin();
                auto iterEnd = field.end();

                json inner;

                for (;iterBegin != iterEnd; ++iterBegin) {
                    auto& instance = *iterBegin;
                    using instanceType = decltype(instance);

                    if constexpr (predicate::has_meta<instanceType>::value)
                        inner.push_back(json_serialize(instance));
                    else {
                        using firstType = typename std::remove_const_t<decltype(instance.first)>;

                        static_assert(std::is_same<firstType, std::string>::value, "Expected key to be a string");

                        inner[instance.first] = json_serialize(instance.second);
                    }
                }

                object[fieldName] = inner;

                return;
            }
        });

        return object;
    }
}

#endif
