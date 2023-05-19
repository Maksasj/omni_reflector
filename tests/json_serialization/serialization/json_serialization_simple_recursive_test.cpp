

#include "test_shared.h"

using namespace std;
using namespace omni::reflector;
using namespace omni::reflector::serialization;

using json = nlohmann::json;

struct MyStruct_0 : public Reflected<MyStruct_0> {
	const constexpr static auto meta = std::make_tuple();
};

struct MyStruct_0_0 : public Reflected<MyStruct_0_0> {
	MyStruct_0 emptyStruct;

	const constexpr static auto meta = std::make_tuple(
		field(emptyStruct)
	);
};

struct MyStruct_1 : public Reflected<MyStruct_1> {
	float floatField;
	double doubleField;
	MyStruct_0 emptyStruct;

	const constexpr static auto meta = std::make_tuple(
		field(floatField),
		field(doubleField),
		field(emptyStruct)
	);
};

struct MyStruct_1_1 : public Reflected<MyStruct_1_1> {
	float floatField;

	const constexpr static auto meta = std::make_tuple(
		field(floatField)
	);
};

struct MyStruct_2 : public Reflected<MyStruct_2> {
	MyStruct_1_1 firstStructField;
	MyStruct_1_1 secondStructField;
	int intField;

	const constexpr static auto meta = std::make_tuple(
		field(firstStructField),
		field(secondStructField),
		field(intField)
	);
};

struct MyStruct_3 : public Reflected<MyStruct_3> {
	MyStruct_2 firstStructField;
	MyStruct_1_1 secondStructField;
	MyStruct_0_0 thirdStructField;

	const constexpr static auto meta = std::make_tuple(
		field(firstStructField),
		field(secondStructField),
		field(thirdStructField)
	);
};

int main() {

	TEST_CASE {
		MyStruct_0_0 testStruct;

		auto data = json_serialize(testStruct);

		ensure(data.size() == 1); // {{}}
	}

	TEST_CASE {
		MyStruct_1 testStruct;

		auto data = json_serialize(testStruct);

		ensure(data.size() == 3);
	}

	TEST_CASE {
		MyStruct_2 testStruct;

		auto data = json_serialize(testStruct);

		ensure(data.size() == 3);
	}

	TEST_CASE {
		MyStruct_3 testStruct;

		auto data = json_serialize(testStruct);

		ensure(data.size() == 3); /* Size returns only top level object size*/
	}

	TEST_CASE {
		MyStruct_1 testStruct;
		testStruct.doubleField = 15.0;
		testStruct.floatField = 7.0f;

		auto data = json_serialize(testStruct);

		ensure(data["doubleField"] == 15.0);
		ensure(data["floatField"] == 7.0f);
	}

	TEST_CASE {
		MyStruct_2 testStruct;
		testStruct.intField = 89;
		testStruct.firstStructField.floatField = 7.0f;
		testStruct.secondStructField.floatField = 77.0f;

		auto data = json_serialize(testStruct);

		ensure(data["intField"] == 89.0);
		ensure(data["firstStructField"]["floatField"] == 7.0f);
		ensure(data["secondStructField"]["floatField"] == 77.0f);
	}

	TEST_CASE {
		MyStruct_3 testStruct;
		testStruct.firstStructField.intField = 89;
		testStruct.firstStructField.firstStructField.floatField = 7.0f;
		testStruct.firstStructField.secondStructField.floatField = 77.0f;
		testStruct.secondStructField.floatField = 78.0f;

		auto data = json_serialize(testStruct);

		ensure(data["firstStructField"]["intField"] == 89.0);
		ensure(data["firstStructField"]["firstStructField"]["floatField"] == 7.0f);
		ensure(data["firstStructField"]["secondStructField"]["floatField"] == 77.0f);
		ensure(data["secondStructField"]["floatField"] == 78.0f);
	}

	return 0;
}