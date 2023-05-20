<div>
  <img align="left" src="https://github.com/Maksasj/omni_reflector/blob/master/docs/omni_reflector_logo_big.gif" width="288px">
  
  # Omni reflector
  Omni reflector - C++ reflection/serialization library, that uses c++ metaprogramming to manage fields of class and structs at compile time. Depends only on c++ standard library, not event boost funsion or hana required. 
  
  *Note serialization api depeneds on [nlohmann/json](https://github.com/nlohmann/json) library*
  
  > omni reflector is not a new javascript framework btw !
  
  Cool looking widgets 
  <img src="https://img.shields.io/github/stars/Maksasj/omni_reflector" alt="stars">
  <img src="https://img.shields.io/github/actions/workflow/status/Maksasj/omni_reflector/cmake.yml" alt="build">
  <img src="https://img.shields.io/github/license/Maksasj/omni_reflector" alt="build">
  
  <br>
</div>

## Usage example
```c++
#define OMNI_REFLECTOR_ENABLE_SERIALIZER
#include "omni_reflector.h"

using namespace omni::reflector;
using namespace omni::reflector::serialization;

struct MyChildStruct : Reflected<MyChildStruct> {
	float someRandomFloatField;

	const constexpr static auto meta = std::make_tuple(
		field(someRandomFloatField)
	);
};

struct MyStruct : Reflected<MyStruct> {
	std::string stringField;
	int poggers;
	MyChildStruct childStruct;

	const constexpr static auto meta = std::make_tuple(
		field(stringField),
		field(poggers),
		field(childStruct)
	);
};

int main() {
	MyStruct someRandomStruct;

	/* Filling struct with some values*/

	nlohmann::json object = json_serialize(someRandomStruct);
	const auto representation = object.dump(4);
	std::cout << representation << "\n";

	return 0;
};
```
After serializing ``someRandomStruct``, eventually we get json structure, that will have following layout *(Note fields fielied with garbage, since I haven't fillied the ``someRandomStruct`` :) )*:
```json
{
    "childStruct": {
        "someRandomFloatField": 4.590373509435236e-41
    },
    "poggers": -981426683,
    "stringField": ""
}
```

## Build
```bash
cmake -B build -G Ninja

make.bat
```

## Testing
```bash
test.bat
```

## License
*Todo*
