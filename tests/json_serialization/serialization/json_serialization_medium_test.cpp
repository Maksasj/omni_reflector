

#include "test_shared.h"

using namespace std;
using namespace omni::reflector;
using namespace omni::reflector::serialization;

using json = nlohmann::json;

struct House : public Reflected<House> {
	float width;
	float height;
	int neighboursCount;
	int stage;

	const constexpr static auto meta = std::make_tuple(
		field(width),
		field(height),
		field(neighboursCount),
		field(stage)
	);
};

struct Mark : public Reflected<Mark> {
	std::string remark;
	float markValue;
	
	Mark(const std::string& _remark, const float& _markValue) : remark(_remark), markValue(_markValue) {}

	const constexpr static auto meta = std::make_tuple(
		field(remark),
		field(markValue)
	);
};

struct Subject : public Reflected<Subject> {
	float depth;
	float maxMark;

	const constexpr static auto meta = std::make_tuple(
		field(depth),
		field(maxMark)
	);
};

struct Adress : public Reflected<Adress> {
	std::string region;
	std::string street;
	House house;

	const constexpr static auto meta = std::make_tuple(
		field(region),
		field(street),
		field(house)
	);
};

struct Student : public Reflected<Student> {
	int age;
	std::vector<Mark> marks;
	std::unordered_map<std::string, Subject> debts;
	Adress adress;
	
	const constexpr static auto meta = std::make_tuple(
		field(age),
		field(marks),
		field(debts),
		field(adress)
	);
};

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

	auto data = json_serialize(testStruct);

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