#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "google/cmockery.h"

void test_io(void **state);


int main(void)
{
    srand(time(NULL));

    const UnitTest tests[] = {
        unit_test(test_io),
    };
    return run_tests(tests);
}



void test_io(void **state)
{
    // TODO
}
