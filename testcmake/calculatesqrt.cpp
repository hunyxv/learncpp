#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "CalculateSqrtConfig.h"
#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Version " << CalculateSqrt_VERSION_MAJOR << " "
                  << CalculateSqrt_VERSION_MINOR << std::endl;
        fprintf(stdout, "Uage: %s number\n", argv[0]);
        return 1;
    }
    double inputValue = atof(argv[1]);
#ifdef USE_MYMATH
    double outputValue = mysqrt(inputValue);
#else
    double outputValue = sqrt(inputValue);
#endif
    fprintf(stdout, "The square root of %g is %g\n", inputValue, outputValue);
    return 0;
}