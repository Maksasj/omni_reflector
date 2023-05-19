#ifndef _OMNI_REFLECTOR_BINARY_SERIALIZE_H_
#define _OMNI_REFLECTOR_BINARY_SERIALIZE_H_

#include <istream>
#include <ostream>

#include "predicates.h"
#include "reflected.h"

namespace omni::reflector::serialization {
    template<class Type> 
    void binary_serialize(std::ostream& stream, const Type& data) {
        if constexpr (predicate::is_not_container<Type>::value && predicate::is_not_reflectable<Type>::value) {
            char* ptr = (char*) (void*) &data;
            stream.write(ptr, sizeof(Type));
        } else {
            for_each_field<predicate::is_any>(data, [&](const char* fieldName, auto& field) {
                using fieldType = typename std::remove_const_t<std::remove_reference_t<decltype(field)>>;

                if constexpr (predicate::is_not_container<fieldType>::value && predicate::is_not_reflectable<fieldType>::value) {
                    fieldType value = field;
                    char* ptr = (char*) (void*) &value;
                    stream.write(ptr, sizeof(fieldType));
                }

                if constexpr (predicate::is_not_container<fieldType>::value && predicate::is_reflectable<fieldType>::value) {
                    binary_serialize(stream, field);
                }

                if constexpr (predicate::is_container<fieldType>::value) {
                    const size_t size = field.size();
                    char* sizePtr = (char*) (void*) &size;
                    stream.write(sizePtr, sizeof(size_t));

                    for(auto element : field) {
                        if constexpr (predicate::is_not_associative<fieldType>::value) {
                            using elementType = typename fieldType::value_type;
                            binary_serialize(stream, element);
                        } else {
                            using firstType = typename std::remove_const_t<decltype(element.first)>;

                            const size_t keySize = element.first.size();
                            char* keySizePtr = (char*) (void*) &keySize;
                            stream.write(keySizePtr, sizeof(size_t));

                            for(auto& letter : element.first)
                                binary_serialize(stream, letter);

                            binary_serialize(stream, element.second);
                        }
                    }
                }
            });
        }
    }

    template<class Type>
    Type binary_deserialize(std::istream& stream) {
        Type object;

        if constexpr (predicate::is_not_container<Type>::value && predicate::is_not_reflectable<Type>::value) {
            char* ptr = (char*) (void*) &object;
            stream.read(ptr, sizeof(Type));
        } else {
            for_each_field<predicate::is_any>(object, [&](const char* fieldName, auto& field) {
                using fieldType = typename std::remove_const_t<std::remove_reference_t<decltype(field)>>;

                if constexpr (predicate::is_not_container<fieldType>::value && predicate::is_not_reflectable<fieldType>::value) {
                    fieldType& value = field;
                    char* ptr = (char*) (void*) &value;
                    stream.read(ptr, sizeof(fieldType));
                }

                if constexpr (predicate::is_not_container<fieldType>::value && predicate::is_reflectable<fieldType>::value) {
                    field = binary_deserialize<fieldType>(stream);
                }

                if constexpr (predicate::is_container<fieldType>::value) {
                    size_t size = 0;
                    char* sizePtr = (char*) (void*) &size;
                    stream.read(sizePtr, sizeof(size_t));

                    using valueType = typename fieldType::value_type;

                    for(int i = 0; i < size; ++i) {
                        if constexpr (predicate::is_not_associative<fieldType>::value) {
                            valueType element = binary_deserialize<valueType>(stream);
                            field.push_back(element);
                        } else {
                            size_t keySize = 0;
                            char* keySizePtr = (char*) (void*) &keySize;
                            stream.read(keySizePtr, sizeof(size_t));

                            std::string key;
                            for(int i = 0; i < keySize; ++i) {
                                auto letter = binary_deserialize<char>(stream);
                                key += letter;
                            }

                            using valueType = typename fieldType::mapped_type;
                            auto element = binary_deserialize<valueType>(stream);
                            field[key] = element;
                        }
                    }
                }
            });
        }


        return object;
    }
}

#endif
