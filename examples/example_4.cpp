#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

using namespace omni::reflector;
using namespace omni::reflector::serialization;

struct MyChildStruct {
	float someRandomFloatField;
};
OMNI_ADAPT_STRUCTURE(MyChildStruct, someRandomFloatField);

struct MyStruct {
	std::string stringField;
	int poggers;
	MyChildStruct childStruct;
};
OMNI_ADAPT_STRUCTURE(MyStruct, stringField, poggers, childStruct);

int main() {
	MyStruct someRandomStruct;

	nlohmann::json object = JsonSerializer::json_serialize(someRandomStruct);
	const auto representation = object.dump(4);
	std::cout << representation << "\n";

	return 0;
};
