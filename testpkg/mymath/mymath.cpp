#include "include/mymath.h"

#include <iostream>

namespace mymath {
int add(int a, int b) {
    std::cout << "Add " << a << b << std::endl;
    return a + b;
}
}  // namespace mymath