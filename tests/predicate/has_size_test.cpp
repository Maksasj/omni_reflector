

#include "test_shared.h"

int main() {
	using namespace std;
	using namespace omni::reflector;

	using CT = int; /* Cork type */

	{
		using testedType = array<CT, 1>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = vector<CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = deque<CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = list<CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = set<CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}


	{
		using testedType = map<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = multiset<CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = multimap<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = unordered_set<CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = unordered_map<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = unordered_multiset<CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	{
		using testedType = unordered_multimap<CT, CT>;

		TEST_CASE {
			ensure_const(predicate::has_size<testedType>::value);
		}
	}

	TEST_CASE {
		ensure_const(negation<predicate::has_size<int>>::value);
	}

	TEST_CASE {
		ensure_const(negation<predicate::has_size<double>>::value);
	}


	TEST_CASE {
		ensure_const(predicate::has_size<string>::value);
	}

	TEST_CASE {
		struct TestStruct {

		};

		ensure_const(negation<predicate::has_size<TestStruct>>::value);
	}


	TEST_CASE {
		struct TestStruct {
			int size() const;
		};

		ensure_const(predicate::has_size<TestStruct>::value);
	}

	TEST_CASE {
		/* Size should const */
		struct TestStruct {
			int size(); 
		};

		ensure_const(negation<predicate::has_size<TestStruct>>::value);
	}

	return 0;
}