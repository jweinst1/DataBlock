#ifndef TEST_MACRO_HEAD
#define TEST_MACRO_HEAD
// Header that contains useful methods for unit test macros

#include <stdio.h>

#define TESTCASE_IS_TRUE(result, n) if(result) printf("TEST %d PASSED\n", n); \
        else printf("TEST %d FAILED\n", n);

#define TESTCASE_IS_EQ(result, expected, n) if(result == expected) printf("TEST %d PASSED\n", n); \
        else printf("TEST %d FAILED\n", n);

#endif // TEST_MACRO_HEAD
