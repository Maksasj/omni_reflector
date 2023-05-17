#include <iostream>
#include <string>
#include <functional>

#include <nlohmann/json.hpp>

#include "omni_reflector.h"

#include <type_traits>

using namespace omni::reflector;

template<class Type> 
nlohmann::json serialize(const Type& data) {
	using json = nlohmann::json;

	json object = json({});

	for_each_field<predicate::is_not_reflectable>(data, [&](const char* fieldName, auto& field) {
		object[fieldName] = field;
	});

	for_each_field<predicate::is_reflectable>(data, [&](const char* fieldName, auto& field) {
		json inner = serialize(field);
		object[fieldName] = inner;
	});

	return object;
}

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
	//std::vector<int> marks;
	//std::unordered_map<std::string, Subject> debts;
	Adress adress;
	
	const constexpr static auto meta = std::make_tuple(
		field(age),
		//field(marks),
		//field(debts),
		field(adress)
	);
};

int main() {
	using json = nlohmann::json;

	Student student;

	student.age = 21;
	// student.marks = { 8, 9, 1 };
	// 
	// student.debts["Math"].depth = 1.0f;
	// student.debts["Math"].maxMark = 10.0f;
	// student.debts["OOP"].depth = 2.0f;
	// student.debts["OOP"].maxMark = 9.0f;

	student.adress.region = "Fabijoniskai";
	student.adress.street = "Kryzioku";
	student.adress.house.width = 1.0f;
	student.adress.house.height = 1.0f;
	student.adress.house.neighboursCount = 2;
	student.adress.house.stage = 5;

	json data = serialize(student);

	const auto representation = data.dump(4);
	std::cout << representation << "\n";
	
	return 0;
}
