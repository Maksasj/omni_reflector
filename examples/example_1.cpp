#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

using namespace omni::reflector;
using namespace omni::reflector::serialization;

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

	std::cout << Reflection<Student>::clearTypeName << "\n";
	std::cout << Reflection<Student>::typeInfo.name() << "\n";
	std::cout << Reflection<Student>::typeInfo.raw_name() << "\n";

	return 0;
}
