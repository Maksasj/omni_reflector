#include <iostream>
#include <string>
#include <functional>

#include <nlohmann/json.hpp>

#include "omni_reflector.h"

using namespace omni::reflector;

struct Adress : public Reflected<Adress> {
	std::string region;
	std::string street;
	int house;
	int stage;

	const constexpr static auto meta = std::make_tuple(
		field(region),
		field(street),
		field(house),
		field(stage)
	);
};

struct Student : public Reflected<Student> {
	int age;
	int mark;
	Adress adress;

	const constexpr static auto meta = std::make_tuple(
		field(age),
		field(mark),
		field(adress)
	);
};

template<class Type> 
nlohmann::json serialize(const Type& data) {
	using json = nlohmann::json;

	json object = json({});

	for_each_field(data, data.meta, [&](const char* fieldName, auto& field) {
		object[fieldName] = field;
	});

	for_each_reflectable_field(data, data.meta, [&](const char* fieldName, auto& field) {
		json inner = serialize(field);
		object[fieldName] = inner;
	});

	return object;
}

int main() {
	using json = nlohmann::json;

	Student student;

	student.age = 21;
	student.mark = 8;
	student.adress.region = "Fabijoniskai";
	student.adress.street = "Kryzioku";
	student.adress.house = 179;
	student.adress.stage = 5;

	json data = serialize(student);

	const auto representation = data.dump(4);
	std::cout << representation;

	return 0;
}