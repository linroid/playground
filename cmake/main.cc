#include <iostream>
#ifdef USE_MY_MATH
#include "math/math.h"
#else
#include <math.h>
#endif
int main()
{
    std::cout << "Hello World" << std::endl;
#ifdef USE_MY_MATH
    std::cout << add(3, 7) << std::endl;
#else
    std::cout << "no math provided" << std::endl;
#endif
    return 0;
}