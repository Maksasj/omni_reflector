

#include "test_shared.h"

using namespace std;
using namespace omni::reflector;
using namespace omni::reflector::serialization;

using json = nlohmann::json;

struct MyStruct_1 {
	std::unordered_map<std::string, int> mapField;

	MyStruct_1() {}
	MyStruct_1(const std::unordered_map<std::string, int>& intMap) : mapField(intMap) {}
};
OMNI_ADAPT_STRUCTURE(MyStruct_1, mapField);

struct MyStruct_2 {
	std::unordered_map<std::string, MyStruct_1> mapField;
};
OMNI_ADAPT_STRUCTURE(MyStruct_2, mapField);

int main() {

	TEST_CASE {
		MyStruct_1 testStruct;
		testStruct.mapField["firstKey"] = 15;
		testStruct.mapField["secondKey"] = 78;
		testStruct.mapField["thirdKey"] =  3;

		auto data = json_serialize(testStruct);

		ensure(data.size() == 1);
	}

	TEST_CASE {
		MyStruct_1 testStruct;
		testStruct.mapField["firstKey"] = 15;
		testStruct.mapField["secondKey"] = 78;
		testStruct.mapField["thirdKey"] =  3;

		auto data = json_serialize(testStruct);

		ensure(data["mapField"].size() == 3);
	}

	TEST_CASE {
		MyStruct_1 testStruct;
		testStruct.mapField["firstKey"] = 15;
		testStruct.mapField["secondKey"] = 78;
		testStruct.mapField["thirdKey"] =  3;

		auto data = json_serialize(testStruct);

		ensure(data["mapField"]["firstKey"] == 15);
		ensure(data["mapField"]["secondKey"] == 78);
		ensure(data["mapField"]["thirdKey"] == 3);
	}

	TEST_CASE {
		MyStruct_2 testStruct;
		testStruct.mapField["firstKey"] = MyStruct_1({ {"firstKey", 15}, {"secondKey", 78}, { "thirdKey", 3 } });
		testStruct.mapField["secondKey"] = MyStruct_1({ {"aaa", 10}, {"bbb", 11}, { "ccc", 12 } });
		testStruct.mapField["thirdKey"] = MyStruct_1({ {"yyy", 1}, {"xxx", 2}, { "ppp", 3 } });

		auto data = json_serialize(testStruct);

		ensure(data.size() == 1);
	}

	TEST_CASE {
		MyStruct_2 testStruct;
		testStruct.mapField["firstKey"] = MyStruct_1({ {"firstKey", 15}, {"secondKey", 78}, { "thirdKey", 3 } });
		testStruct.mapField["secondKey"] = MyStruct_1({ {"aaa", 10}, {"bbb", 11}, { "ccc", 12 } });
		testStruct.mapField["thirdKey"] = MyStruct_1({ {"yyy", 1}, {"xxx", 2}, { "ppp", 3 } });

		auto data = json_serialize(testStruct);

		ensure(data["mapField"].size() == 3);
	}

	TEST_CASE {
		MyStruct_2 testStruct;
		testStruct.mapField["firstKey"] = MyStruct_1({ {"firstKey", 15}, {"secondKey", 78}, { "thirdKey", 3 } });
		testStruct.mapField["secondKey"] = MyStruct_1({ {"aaa", 10}, {"bbb", 11}, { "ccc", 12 } });
		testStruct.mapField["thirdKey"] = MyStruct_1({ {"yyy", 1}, {"xxx", 2}, { "ppp", 3 } });

		auto data = json_serialize(testStruct);

		ensure(data["mapField"]["firstKey"]["mapField"].size() == 3);
		ensure(data["mapField"]["secondKey"]["mapField"].size() == 3);
		ensure(data["mapField"]["thirdKey"]["mapField"].size() == 3);
	}

	TEST_CASE {
		MyStruct_2 testStruct;
		testStruct.mapField["firstKey"] = MyStruct_1({ {"firstKey", 15}, {"secondKey", 78}, { "thirdKey", 3 } });
		testStruct.mapField["secondKey"] = MyStruct_1({ {"aaa", 10}, {"bbb", 11}, { "ccc", 12 } });
		testStruct.mapField["thirdKey"] = MyStruct_1({ {"yyy", 1}, {"xxx", 2}, { "ppp", 3 } });

		auto data = json_serialize(testStruct);

		ensure(data["mapField"]["firstKey"]["mapField"]["firstKey"] == 15);
		ensure(data["mapField"]["firstKey"]["mapField"]["secondKey"] == 78);
		ensure(data["mapField"]["firstKey"]["mapField"]["thirdKey"] == 3);

		ensure(data["mapField"]["secondKey"]["mapField"]["aaa"] == 10);
		ensure(data["mapField"]["secondKey"]["mapField"]["bbb"] == 11);
		ensure(data["mapField"]["secondKey"]["mapField"]["ccc"] == 12);

		ensure(data["mapField"]["thirdKey"]["mapField"]["yyy"] == 1);
		ensure(data["mapField"]["thirdKey"]["mapField"]["xxx"] == 2);
		ensure(data["mapField"]["thirdKey"]["mapField"]["ppp"] == 3);
	}

	return 0;
}