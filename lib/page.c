#include "page.h"

struct file_header_t {
    uint16_t magic_number;
    uint16_t size_per_page;
    uint32_t free_page_count;
    uint32_t free_page_list;
};
