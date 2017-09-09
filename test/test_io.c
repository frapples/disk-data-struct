#include "cmockery-inc.h"
#include "io.h"

void test_memfile_io(IoFile* f, io_off_t off) {
    char buf[1024];

    char data[] = "abdefgiajd";
    assert_int_equal(io_write(f, off, data, sizeof(data)), sizeof(data));
    assert_int_equal(io_read(f, off, buf, sizeof(data)), sizeof(data));
    assert_true(memcmp(buf, data, sizeof(data)) == 0);
    memset(buf, 0x0, sizeof(buf));
    assert_int_equal(io_read(f, off, buf, sizeof(data)), sizeof(data));
    assert_true(memcmp(buf, data, sizeof(data)) == 0);
}

void test_io_memfile(void **state)
{
    IoFile* f = io_open(":memory:", NULL);

    char buf[1024];
    assert_int_equal(io_read(f, 0, buf, sizeof(buf)), 0);

    test_memfile_io(f, 0);
    test_memfile_io(f, 1024);
    test_memfile_io(f, 512);

    io_close(f);
}
