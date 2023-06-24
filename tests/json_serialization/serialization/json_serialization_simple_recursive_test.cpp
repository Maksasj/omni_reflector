

#include "test_shared.h"

using namespace std;
using namespace omni::reflector;
using namespace omni::reflector::serialization;

using json = nlohmann::json;

struct MyStruct_0 {
	
};
OMNI_ADAPT_STRUCTURE(MyStruct_0);

struct MyStruct_0_0 {
	MyStruct_0 emptyStruct;
};
OMNI_ADAPT_STRUCTURE(MyStruct_0_0, emptyStruct);

struct MyStruct_1 {
	float floatField;
	double doubleField;
	MyStruct_0 emptyStruct;
};
OMNI_ADAPT_STRUCTURE(MyStruct_1, floatField, doubleField, emptyStruct);

struct MyStruct_1_1 {
	float floatField;
};
OMNI_ADAPT_STRUCTURE(MyStruct_1_1, floatField);

struct MyStruct_2 {
	MyStruct_1_1 firstStructField;
	MyStruct_1_1 secondStructField;
	int intField;
};
OMNI_ADAPT_STRUCTURE(MyStruct_2, firstStructField, secondStructField, intField);

struct MyStruct_3 {
	MyStruct_2 firstStructField;
	MyStruct_1_1 secondStructField;
	MyStruct_0_0 thirdStructField;
};
OMNI_ADAPT_STRUCTURE(MyStruct_3, firstStructField, secondStructField, thirdStructField);

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