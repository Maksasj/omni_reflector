

#include "test_shared.h"

int main() {
	using namespace std;
	using namespace omni::reflector;

	using CT = int; /* Cork type */

	{
		using testedType = array<CT, 1>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = vector<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = deque<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = forward_list<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = list<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = set<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = map<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = multiset<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = multimap<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = unordered_set<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = unordered_map<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = unordered_multiset<CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	{
		using testedType = unordered_multimap<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_all_end<testedType>::value);
		}

		TEST_CASE {
			ensure_const(predicate::has_any_end<testedType>::value);
		}
	}

	TEST_CASE {
		ensure_const(negation<predicate::has_any_end<int>>::value);
		ensure_const(negation<predicate::has_all_end<int>>::value);
	}

	TEST_CASE {
		ensure_const(negation<predicate::has_any_end<double>>::value);
		ensure_const(negation<predicate::has_all_end<double>>::value);
	}

	TEST_CASE {
		ensure_const(predicate::has_any_end<string>::value);
		ensure_const(predicate::has_all_end<string>::value);
	}

	TEST_CASE {
		struct MyStruct {

		};

		ensure_const(negation<predicate::has_any_end<MyStruct>>::value);
		ensure_const(negation<predicate::has_all_end<MyStruct>>::value);
	}

	TEST_CASE {
		struct MyStruct {
			int end();
			int end() const;
		};

		ensure_const(predicate::has_all_end<MyStruct>::value);
		ensure_const(predicate::has_any_end<MyStruct>::value);
		ensure_const(predicate::has_const_end<MyStruct>::value);
		ensure_const(predicate::has_nonconst_end<MyStruct>::value);
	}

	TEST_CASE {
		struct MyStruct {
			int end();
		};

		ensure_const(negation<predicate::has_all_end<MyStruct>>::value);
		ensure_const(predicate::has_any_end<MyStruct>::value);
		ensure_const(predicate::has_nonconst_end<MyStruct>::value);
		ensure_const(negation<predicate::has_const_end<MyStruct>>::value);
	}

	return 0;
}