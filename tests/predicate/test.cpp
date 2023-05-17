int main() {
    if constexpr (predicate::has_begin<std::unordered_map<int, int>>::value) {
		std::cout << "yes !\n";
	} else {
		std::cout << "no !\n";
	}

	if constexpr (predicate::has_begin<std::vector<int>>::value) {
		std::cout << "yes !\n";
	} else {
		std::cout << "no !\n";
	}

	if constexpr (predicate::has_begin<int>::value) {
		std::cout << "yes !\n";
	} else {
		std::cout << "no !\n";
	}

	if constexpr (predicate::has_begin<std::string>::value) {
		std::cout << "yes !\n";
	} else {
		std::cout << "no !\n";
	}

	if constexpr (predicate::has_begin<Student>::value) {
		std::cout << "yes !\n";
	} else {
		std::cout << "no !\n";
	}
}