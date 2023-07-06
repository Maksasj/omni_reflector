#ifndef _OMNI_REFLECTOR_BINARY_SERIALIZE_H_
#define _OMNI_REFLECTOR_BINARY_SERIALIZE_H_

#include <istream>
#include <ostream>

#include "predicates.h"
#include "reflection.h"

namespace omni::reflector::serialization {
    struct BinarySerializer {
        template<class Type> 
        static void binary_serialize(std::ostream& stream, const Type& data) {
            if constexpr (predicate::is_not_container<Type>::value && predicate::is_not_reflectable<Type>::value) {
                char* ptr = (char*) (void*) &data;
                stream.write(ptr, sizeof(Type));

                return;
            }

            if constexpr (predicate::is_container<Type>::value && predicate::is_not_reflectable<Type>::value) {
                binary_serialize(stream, data.size());

                for(const auto& element : data) {
                    if constexpr (predicate::is_not_associative<Type>::value) {
                        binary_serialize(stream, element);
                    } else {
                        binary_serialize(stream, element.first);
                        binary_serialize(stream, element.second);
                    }
                }

                return;
            }

            if constexpr (predicate::is_reflectable<Type>::value) {
                FieldFriendlyScope::for_each_field<predicate::is_any>(data, [&](const char* fieldName, auto& field) {
                    (void) fieldName;

                    binary_serialize(stream, field);
                });

                return;
            }
        }

        template<class Type>
        static Type binary_deserialize(std::istream& stream) {
            Type object;

            if constexpr (predicate::is_not_container<Type>::value && predicate::is_not_reflectable<Type>::value) {
                char* ptr = (char*) (void*) &object;
                stream.read(ptr, sizeof(Type));
            }

            if constexpr (predicate::is_container<Type>::value) {
                const size_t size = binary_deserialize<size_t>(stream);

                using valueType = typename Type::value_type;

                for(size_t i = 0; i < size; ++i) {
                    if constexpr (predicate::is_not_associative<Type>::value) {
                        object.push_back(binary_deserialize<valueType>(stream));
                    } else {
                        const std::string key = binary_deserialize<std::string>(stream);
                        object[key] = binary_deserialize<typename Type::mapped_type>(stream);
                    }
                }
            }

            if constexpr (predicate::is_reflectable<Type>::value) {
                FieldFriendlyScope::for_each_field<predicate::is_any>(object, [&](const char* fieldName, auto& field) {
                    using fieldType = typename std::remove_const_t<std::remove_reference_t<decltype(field)>>;

                    (void) fieldName;

                    field = binary_deserialize<fieldType>(stream);
                });
            }

            return object;
        }
    };
}

#endif
