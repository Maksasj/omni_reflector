#include <iostream>
#include <string>
#include <functional>

#include <nlohmann/json.hpp>

#include "omni_reflector.h"

using namespace omni::reflector;

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
	int mark;
	Adress adress;
	
	const constexpr static auto meta = std::make_tuple(
		field(age),
		field(mark),
		field(adress)
	);
};

int main() {
	using json = nlohmann::json;

	Student student = (Student) {
		.age = 21,
		.mark = 8,
		.adress = (Adress) {
			.region = "Fabijoniskai",
			.street = "Kryzioku", 
			.house = (House) {
				.width = 1.0f,
				.height = 1.0f,
				.neighboursCount = 2,
				.stage = 5
			}
		}
	};

	json data = serialize(student);

	const auto representation = data.dump(4);
	std::cout << representation;

	return 0;
}