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

	for_each_field<predicate::is_any>(data, [&](const char* fieldName, auto& field) {
		using fieldType = typename std::remove_const_t<std::remove_reference_t<decltype(field)>>;
		
		if constexpr (predicate::is_assignable<json, fieldType>::value) {
			object[fieldName] = field;
			return;
		}
		
		if constexpr (predicate::is_reflectable<fieldType>::value) {
			json inner = serialize(field);
			object[fieldName] = inner;
			return;
		}

		if constexpr (predicate::has_any_begin<fieldType>::value && predicate::has_any_end<fieldType>::value && predicate::is_not_assignable<json, fieldType>::value) {
			auto iterBegin = field.begin();
			auto iterEnd = field.end();

			json inner;

			for (;iterBegin != iterEnd; ++iterBegin) {
				auto& instance = *iterBegin;
				using instanceType = decltype(instance);

				if constexpr (predicate::has_meta<instanceType>::value)
					inner.push_back(serialize(instance));
				else {
					using firstType = typename std::remove_const_t<decltype(instance.first)>;

					static_assert(std::is_same<firstType, std::string>::value, "Expected key to be a string");

					inner[instance.first] = serialize(instance.second);
				}
			}

			object[fieldName] = inner;

			return;
		}
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

	json data = serialize(student);

	const auto representation = data.dump(4);
	std::cout << representation << "\n";

	return 0;
}
