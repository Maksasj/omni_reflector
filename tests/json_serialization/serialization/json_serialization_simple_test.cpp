

#include "test_shared.h"

using namespace std;
using namespace omni::reflector;
using namespace omni::reflector::serialization;

using json = nlohmann::json;

struct MyStruct_0 : public Reflected<MyStruct_0> {
	const constexpr static auto meta = std::make_tuple();
};

struct MyStruct_1 : public Reflected<MyStruct_1> {
	float floatField;
	double doubleField;
	int intField;

	const constexpr static auto meta = std::make_tuple(
		field(floatField),
		field(doubleField),
		field(intField)
	);
};

struct MyStruct_2 : public Reflected<MyStruct_2> {
	float floatField;
	double doubleField;
	int intField;
	char charField;

	const constexpr static auto meta = std::make_tuple(
		field(floatField),
		field(doubleField),
		field(intField),
		field(charField)
	);
};

int main() {

	TEST_CASE {
		MyStruct_0 testStruct;

		auto data = json_serialize(testStruct);

		ensure(data.size() == 0);
	}

	TEST_CASE {
		MyStruct_1 testStruct;

		auto data = json_serialize(testStruct);

		ensure(data.size() == 3);
	}

	TEST_CASE {
		MyStruct_2 testStruct;

		auto data = json_serialize(testStruct);

		ensure(data.size() == 4);
	}

	TEST_CASE {
		MyStruct_1 testStruct;
		testStruct.doubleField = 15.0;
		testStruct.floatField = 7.0f;
		testStruct.intField = 89;

		auto data = json_serialize(testStruct);

		ensure(data["doubleField"] == 15.0);
		ensure(data["floatField"] == 7.0f);
		ensure(data["intField"] == 89);
	}

	TEST_CASE {
		MyStruct_2 testStruct;
		testStruct.doubleField = 15.0;
		testStruct.floatField = 7.0f;
		testStruct.intField = 89;
		testStruct.charField = 127;

		auto data = json_serialize(testStruct);

		ensure(data["doubleField"] == 15.0);
		ensure(data["floatField"] == 7.0f);
		ensure(data["intField"] == 89);
		ensure(data["charField"] == 127);
	}

	return 0;
}