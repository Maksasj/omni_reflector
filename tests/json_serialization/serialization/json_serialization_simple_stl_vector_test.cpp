

#include "test_shared.h"

using namespace std;
using namespace omni::reflector;
using namespace omni::reflector::serialization;

using json = nlohmann::json;

struct MyStruct_1 {
	std::vector<int> vectorField;

	MyStruct_1() {}
	MyStruct_1(const std::vector<int>& intVector) : vectorField(intVector) {}
};
OMNI_ADAPT_STRUCTURE(MyStruct_1, vectorField);

struct MyStruct_2 {
	std::vector<MyStruct_1> vectorField;
};
OMNI_ADAPT_STRUCTURE(MyStruct_2, vectorField);

int main() {

	TEST_CASE {
		MyStruct_1 testStruct;
		testStruct.vectorField = { 15, 75, 98, 14, 9 };

		auto data = json_serialize(testStruct);

		ensure(data.size() == 1);
	}

	TEST_CASE {
		MyStruct_1 testStruct;
		testStruct.vectorField = { 15, 75, 98, 14, 9 };

		auto data = json_serialize(testStruct);

		ensure(data["vectorField"].size() == 5);
	}

	TEST_CASE {
		MyStruct_1 testStruct;
		testStruct.vectorField = { 15, 75, 98, 14, 9 };

		auto data = json_serialize(testStruct);

		ensure(data["vectorField"][0] == 15);
		ensure(data["vectorField"][1] == 75);
		ensure(data["vectorField"][2] == 98);
		ensure(data["vectorField"][3] == 14);
		ensure(data["vectorField"][4] == 9);
	}

	TEST_CASE {
		MyStruct_2 testStruct;
		testStruct.vectorField.push_back(MyStruct_1({ 15, 75, 98, 14, 9 }));
		testStruct.vectorField.push_back(MyStruct_1({ 78, 1, 8, 26, 47 }));
		testStruct.vectorField.push_back(MyStruct_1({ 1, 2, 3, 4, 5 }));

		auto data = json_serialize(testStruct);

		ensure(data.size() == 1);
	}

	TEST_CASE {
		MyStruct_2 testStruct;
		testStruct.vectorField.push_back(MyStruct_1({ 15, 75, 98, 14, 9 }));
		testStruct.vectorField.push_back(MyStruct_1({ 78, 1, 8, 26, 47 }));
		testStruct.vectorField.push_back(MyStruct_1({ 1, 2, 3, 4, 5 }));

		auto data = json_serialize(testStruct);

		ensure(data["vectorField"].size() == 3);
	}

	TEST_CASE {
		std::vector<int> firstVector = { 15, 75, 98, 14, 9 };

		MyStruct_2 testStruct;
		testStruct.vectorField.push_back(MyStruct_1(firstVector));
		testStruct.vectorField.push_back(MyStruct_1({ 78, 1, 8, 26, 47 }));
		testStruct.vectorField.push_back(MyStruct_1({ 1, 2, 3, 4, 5 }));
		testStruct.vectorField.push_back(MyStruct_1({ 0 }));

		auto data = json_serialize(testStruct);

		ensure(data["vectorField"][0].size() == 1);
		ensure(data["vectorField"][0]["vectorField"].size() == 5);

		for(int i = 0; i < 5; ++i) 
			ensure(data["vectorField"][0]["vectorField"][i] == firstVector[i]);

		ensure(data["vectorField"][1].size() == 1);
		ensure(data["vectorField"][1]["vectorField"].size() == 5);

		ensure(data["vectorField"][2].size() == 1);
		ensure(data["vectorField"][2]["vectorField"].size() == 5);
		
		ensure(data["vectorField"][3].size() == 1);
		ensure(data["vectorField"][3]["vectorField"].size() == 1);
	}

	return 0;
}