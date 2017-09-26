#include "btree.h"

struct btree_node_t {
    uint64_t indexes[M - 1];
    io_off_t data_ptrs[M];
    io_off_t children[M];
};

struct btree_t {
    file_header_t* file_header;
    io_off_t root_node;
};

void btree_init(btree_t* btree, file_header_t* file_header, io_off_t root_node)
{
    btree->file_header = file_header;
    btree->root_node = root_node;
}
