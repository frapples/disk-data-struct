#ifndef __BTREE_H__RAND936129428292858383414475510299913269
#define __BTREE_H__RAND936129428292858383414475510299913269

#include <stdio.h>
#include <stdint.h>
#include "io.h"

#define M 128

/*
  1. The root node and the free list are saved by the caller
 */

typedef struct {
    io_file_t* iofile;

    io_off_t free_node_list;
} btree_io_file_t;

typedef struct {
    uint64_t indexes[M - 1];
    io_off_t data_ptrs[M];
    io_off_t children[M];
} btree_node_t;

typedef struct {
    btree_io_file_t* btree_io_file;
    io_off_t root_node;
} btree_t;

void btree_io_file_init(btree_io_file_t* btree_io_file, io_file_t* iofile);
void btree_io_file_close(btree_io_file_t* btree_io_file);

void btree_init(btree_t* btree, btree_io_file_t* btree_io_file, io_off_t free_node_list);

void btree_open(btree_t* btree);
void btree_close(btree_t* btree);

io_off_t btree_get(btree_t* btree, uint64_t key);
void btree_remove(btree_t* btree, uint64_t key);
void btree_put(btree_t* btree, uint64_t key, io_off_t data);
void btree_destory(btree_t* btree);


#endif /* __BTREE_H__RAND936129428292858383414475510299913269 */
