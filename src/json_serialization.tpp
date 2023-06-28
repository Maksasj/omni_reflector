#ifndef _OMNI_REFLECTOR_JSON_SERIALIZE_H_
#define _OMNI_REFLECTOR_JSON_SERIALIZE_H_

#include <nlohmann/json.hpp>

#include "predicates.h"
#include "reflection.h"

namespace omni::reflector::serialization {
    struct JsonSerializer {
        template<class Type> 
        static nlohmann::json json_serialize(const Type& data) {
            using json = nlohmann::json;

            if constexpr (predicate::is_assignable<json, Type>::value)
                return data;

            if constexpr (predicate::is_container<Type>::value && predicate::is_not_reflectable<Type>::value && predicate::is_not_assignable<json, Type>::value) {
                json object;

                if constexpr (predicate::is_not_associative<Type>::value) {
                    object = json::array();

                    for(auto& instance : data)
                        object.push_back(json_serialize(instance));
                } else {
                    object = json::object();
                    
                    for(auto& instance : data) {
                        using firstType = typename std::remove_const_t<decltype(instance.first)>;

                        static_assert(std::is_same<firstType, std::string>::value, "Expected key to be a string");

                        object[instance.first] = json_serialize(instance.second);
                    }
                }
                
                return object;
            }

            if constexpr (predicate::is_reflectable<Type>::value) {
                json object = json::object();

                FieldFriendlyScope::for_each_field<predicate::is_any>(data, [&](const char* fieldName, auto& field) {
                    object[fieldName] = json_serialize(field);
                });

                return object;
            }

            return json::object();
        }

        template<class Type> 
        static auto json_deserialize(const nlohmann::json& data) -> Type {
            using json = nlohmann::json;
            
            Type object;

            if constexpr (predicate::is_assignable<json, Type>::value) {
                object = data;
            }

            if constexpr (predicate::has_any_begin<Type>::value && predicate::has_any_end<Type>::value && predicate::is_not_assignable<json, Type>::value) {
                using valueType = typename Type::value_type;

                for (auto& sub : data.items()) {
                    if constexpr (predicate::is_associative<Type>::value)
                        object[sub.key()] = json_deserialize<typename Type::mapped_type>(sub.value());
                    else
                        object.push_back(json_deserialize<valueType>(sub.value()));
                }
            }

            if constexpr (predicate::is_reflectable<Type>::value) {
                FieldFriendlyScope::for_each_field<predicate::is_any>(object, [&](const char* fieldName, auto& field) {
                    using fieldType = typename std::remove_const_t<std::remove_reference_t<decltype(field)>>;
                    field = json_deserialize<fieldType>(data[fieldName]);
                });
            }

            return object;
        }
    };
}

#endif
