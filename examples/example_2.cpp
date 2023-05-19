#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

#include "omni_reflector.h"
#include "omni_serializer.h"

using namespace omni::reflector;
using namespace omni::reflector::serialization;

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

	Mark() {}
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
	using json = nlohmann::json;

	Student student;

	student.age = 21;
	student.marks.push_back(Mark("bad english", 6.0f));
	student.marks.push_back(Mark("bad math", 4.0f));
	student.marks.push_back(Mark("good pe", 9.0f));

	student.debts["Math"].depth = 1.0f;
	student.debts["Math"].maxMark = 10.0f;
	student.debts["OOP"].depth = 2.0f;
	student.debts["OOP"].maxMark = 9.0f;

	student.adress.region = "Fabijoniskai";
	student.adress.street = "Kryzioku";
	student.adress.house.width = 1.0f;
	student.adress.house.height = 1.0f;
	student.adress.house.neighboursCount = 2;
	student.adress.house.stage = 5;

	json data = json_serialize(student);
	const auto representation = data.dump(4);
	std::cout << representation << "\n";

	Student newStudent = json_deserialize<Student>(data);
	json newData = json_serialize(newStudent);
	const auto newRepresentation = newData.dump(4);
	std::cout << newRepresentation << "\n";

	return 0;
}
