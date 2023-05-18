#include "test_shared.h"


int main() {
    using namespace std;
	using namespace omni::reflector;

    struct MyStruct {};
    struct MyStructButReflectable : Reflected<MyStructButReflectable> {};

    TEST_CASE {
        ensure_const(predicate::is_reflectable<MyStructButReflectable>::value);
        ensure_const(negation<predicate::is_reflectable<MyStruct>>::value);
    }

    TEST_CASE {
        ensure_const(predicate::is_not_reflectable<MyStruct>::value);
        ensure_const(negation<predicate::is_not_reflectable<MyStructButReflectable>>::value);
    }
    
    TEST_CASE {
        ensure_const(predicate::is_not_reflectable<int>::value);
        ensure_const(predicate::is_not_reflectable<float>::value);
    }

    TEST_CASE {
        ensure_const(predicate::is_not_reflectable<string>::value);
        ensure_const(predicate::is_not_reflectable<vector<int>>::value);
    }

	return 0;
}