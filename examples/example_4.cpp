#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

using namespace omni::reflector;
using namespace omni::reflector::serialization;

struct MyChildStruct : Reflected<MyChildStruct> {
	float someRandomFloatField;

	const constexpr static auto meta = std::make_tuple(
		field(someRandomFloatField)
	);
};

struct MyStruct : Reflected<MyStruct> {
	std::string stringField;
	int poggers;
	MyChildStruct childStruct;

	const constexpr static auto meta = std::make_tuple(
		field(stringField),
		field(poggers),
		field(childStruct)
	);
};

int main() {
	MyStruct someRandomStruct;

	nlohmann::json object = json_serialize(someRandomStruct);
	const auto representation = object.dump(4);
	std::cout << representation << "\n";

	return 0;
};
