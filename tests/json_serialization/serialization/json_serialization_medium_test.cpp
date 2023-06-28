

#include "test_shared.h"

using namespace std;
using namespace omni::reflector;
using namespace omni::reflector::serialization;

using json = nlohmann::json;

struct House {
	float width;
	float height;
	int neighboursCount;
	int stage;
};
OMNI_ADAPT_STRUCTURE(House, width, height, neighboursCount, stage);

struct Mark {
	std::string remark;
	float markValue;
	
	Mark(const std::string& _remark, const float& _markValue) : remark(_remark), markValue(_markValue) {}
};
OMNI_ADAPT_STRUCTURE(Mark, remark, markValue);

struct Subject {
	float depth;
	float maxMark;
};
OMNI_ADAPT_STRUCTURE(Subject, depth, maxMark);

struct Adress {
	std::string region;
	std::string street;
	House house;
};
OMNI_ADAPT_STRUCTURE(Adress, region, street, house);

struct Student {
	int age;
	std::vector<Mark> marks;
	std::unordered_map<std::string, Subject> debts;
	Adress adress;
};
OMNI_ADAPT_STRUCTURE(Student, age, marks, debts, adress);

int main() {
	Student testStruct;

	testStruct.age = 21;
	testStruct.marks.push_back(Mark("bad english", 6.0f));
	testStruct.marks.push_back(Mark("bad math", 4.0f));
	testStruct.marks.push_back(Mark("good pe", 9.0f));

	testStruct.debts["Math"].depth = 1.0f;
	testStruct.debts["Math"].maxMark = 10.0f;
	testStruct.debts["OOP"].depth = 2.0f;
	testStruct.debts["OOP"].maxMark = 9.0f;

	testStruct.adress.region = "Fabijoniskai";
	testStruct.adress.street = "Kryzioku";
	testStruct.adress.house.width = 1.0f;
	testStruct.adress.house.height = 1.0f;
	testStruct.adress.house.neighboursCount = 2;
	testStruct.adress.house.stage = 5;

	auto data = JsonSerializer::json_serialize(testStruct);

	TEST_CASE {
		ensure(data.size() == 4);
	}

	TEST_CASE {
		ensure(data["age"] == 21);
	}

	TEST_CASE {
		ensure(data["marks"].size() == 3);
	}

	TEST_CASE {
		ensure(data["marks"][0].size() == 2);
	}
	
	TEST_CASE {
		ensure(data["marks"][0]["remark"] == "bad english");
		ensure(data["marks"][0]["markValue"] == 6.0f);

		ensure(data["marks"][1]["remark"] == "bad math");
		ensure(data["marks"][1]["markValue"] == 4.0f);

		ensure(data["marks"][2]["remark"] == "good pe");
		ensure(data["marks"][2]["markValue"] == 9.0f);
	}

	TEST_CASE {
		ensure(data["debts"].size() == 2);
	}

	TEST_CASE {
		ensure(data["debts"]["Math"]["depth"] == 1.0f);
		ensure(data["debts"]["Math"]["maxMark"] == 10.0f);

		ensure(data["debts"]["OOP"]["depth"] == 2.0f);
		ensure(data["debts"]["OOP"]["maxMark"] == 9.0f);
	}

	TEST_CASE {
		ensure(data["adress"]["region"] == "Fabijoniskai");
		ensure(data["adress"]["street"] == "Kryzioku");
		ensure(data["adress"]["house"]["neighboursCount"] == 2);
	}

	return 0;
}