#ifndef MY_ASSERT_H
#define MY_ASSERT_H

#include <iostream>
#include <cstdlib> 
#define MY_ASSERT(cond) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed: " << #cond \
                      << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
            std::abort(); \
        } \
    } while (0)

#endif
