

#include "test_shared.h"

int main() {
	using namespace std;
	using namespace omni::reflector;

	using CT = int; /* Cork type */

	{
		using testedType = array<CT, 1>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = vector<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = deque<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = forward_list<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = list<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = set<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = map<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = multiset<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = multimap<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = unordered_set<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = unordered_map<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = unordered_multiset<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	{
		using testedType = unordered_multimap<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_begin<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_begin<testedType>::value);
		}
	}

	TEST_CASE {
		ensure_const(negation<predicate::has_any_begin<int>>::value);
		ensure_const(negation<predicate::has_all_begin<int>>::value);
	}

	TEST_CASE {
		ensure_const(negation<predicate::has_any_begin<double>>::value);
		ensure_const(negation<predicate::has_all_begin<double>>::value);
	}

	TEST_CASE {
		ensure_const(predicate::has_any_begin<string>::value);
		ensure_const(predicate::has_all_begin<string>::value);
	}

	TEST_CASE {
		struct TestStruct {

		};

		ensure_const(negation<predicate::has_any_begin<TestStruct>>::value);
		ensure_const(negation<predicate::has_all_begin<TestStruct>>::value);
	}

	TEST_CASE {
		struct TestStruct {
			int begin();
			int begin() const;
		};

		ensure_const(predicate::has_all_begin<TestStruct>::value);
		ensure_const(predicate::has_any_begin<TestStruct>::value);
		ensure_const(predicate::has_const_begin<TestStruct>::value);
		ensure_const(predicate::has_nonconst_begin<TestStruct>::value);
	}

	TEST_CASE {
		struct TestStruct {
			int begin();
		};

		ensure_const(negation<predicate::has_all_begin<TestStruct>>::value);
		ensure_const(predicate::has_any_begin<TestStruct>::value);
		ensure_const(predicate::has_nonconst_begin<TestStruct>::value);
		ensure_const(negation<predicate::has_const_begin<TestStruct>>::value);
	}

	return 0;
}