#ifndef _OMNI_REFLECTOR_TESTING_TEST_SHARED_H_
#define _OMNI_REFLECTOR_TESTING_TEST_SHARED_H_

#include "stl_containers.h"

#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

#define ensure(EXP) if(!(EXP)) return 1;
#define ensure_const(EXP) if constexpr (!(EXP)) return 1;
#define TEST_CASE

#endif
