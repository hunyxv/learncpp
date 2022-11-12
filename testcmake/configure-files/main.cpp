#include <iostream>

#include "path.h"
#include "ver.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello Version " << ver << "!" << std::endl;
    std::cout << "Path is " << path << std::endl;
    return 0;
}