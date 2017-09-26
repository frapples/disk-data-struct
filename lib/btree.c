#include "btree.h"

struct btree_node_t {
    uint64_t indexes[M - 1];
    io_off_t data_ptrs[M];
    page_no_t children[M];
};

struct btree_t {
    file_pages_t* file_pages;
    io_off_t root_node;
};

void btree_init(btree_t* btree, file_pages_t* file_pages, io_off_t root_node)
{
    btree->file_pages = file_pages;
    btree->root_node = root_node;
}
