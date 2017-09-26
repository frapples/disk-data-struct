#include "page.h"

#include <stdio.h>
#include <assert.h>
#include "serialize.h"

#define MAGIC_NUMBER 0xabcd
#define DEFAULT_SIZE_PER_PAGE 512
/*
  1. The file is treated as a page array
  2. The page index starts at 1, and the 0 index is treated like a NULL effect
 */

struct file_pages_t {
    io_file_t* io_file;

    uint16_t magic_number;
    uint16_t size_per_page;
    uint32_t free_page_count;
    page_no_t free_page_list;
};

static void file_pages_load(file_pages_t* file_pages, io_file_t* io_file);
static void file_pages_dump(const file_pages_t* file_pages, io_file_t* io_file);

void file_pages_init(file_pages_t* file_pages, io_file_t* io_file)
{
    file_pages->io_file = io_file;
    file_pages_load(file_pages, io_file);
}

void file_pages_format(io_file_t* io_file)
{
    file_pages_t file_pages;
    file_pages.magic_number = MAGIC_NUMBER;
    file_pages.size_per_page = DEFAULT_SIZE_PER_PAGE;
    file_pages.free_page_count = 0;
    file_pages.free_page_list = PAGE_NO_NULL;

    file_pages_dump(&file_pages, io_file);
}

void page_read(file_pages_t* file_pages, page_no_t no, char buf[])
{
    assert(no > 0);

    io_read(file_pages->io_file, file_pages->size_per_page * (no - 1), buf, file_pages->size_per_page);
}

void page_write(file_pages_t* file_pages, page_no_t no, const char buf[])
{
    assert(no > 0);

    io_write(file_pages->io_file, file_pages->size_per_page * (no - 1), buf, file_pages->size_per_page);
}

static void file_pages_load(file_pages_t* file_pages, io_file_t* io_file)
{
    /* FIXME: Ignore byte order and memory layout */
    io_read(io_file, 0, (char *)(&file_pages->magic_number), STRUCT_SIZE_START_FORM_MEMBER(file_pages_t, magic_number));

    assert(file_pages->magic_number == MAGIC_NUMBER);

    if (file_pages->size_per_page % 512 != 0) {
        fprintf(stderr, "Warning: the size of per page is not a multiple of 512, it's %d\n", file_pages->size_per_page);
    }
}

static void file_pages_dump(const file_pages_t* file_pages, io_file_t* io_file)
{
    /* FIXME: Ignore byte order and memory layout */
    io_write(io_file, 0, (const char*)(&file_pages->magic_number), STRUCT_SIZE_START_FORM_MEMBER(file_pages_t, magic_number));
}
