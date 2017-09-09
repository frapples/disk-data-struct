#include "cmockery-inc.h"
#include "io.h"

void test_io_memfile(void **state);


int main(void)
{
    srand(time(NULL));

    const UnitTest tests[] = {
        unit_test(test_io_memfile),
    };
    return run_tests(tests);
}
