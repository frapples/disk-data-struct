#ifndef __BTREE_H__RAND936129428292858383414475510299913269
#define __BTREE_H__RAND936129428292858383414475510299913269

#include <stdio.h>
#include <stdint.h>
#include "io.h"
#include "page.h"

#define M 128

/*
  1. The root node and the free list are saved by the caller
 */

typedef struct btree_node_t btree_node_t;
typedef struct btree_t btree_t;

void btree_init(btree_t* btree, file_pages_t* file_pages, io_off_t root_node);

void btree_open(btree_t* btree);
void btree_close(btree_t* btree);

io_off_t btree_get(btree_t* btree, uint64_t key);
void btree_remove(btree_t* btree, uint64_t key);
void btree_put(btree_t* btree, uint64_t key, io_off_t data);
void btree_destory(btree_t* btree);


#endif /* __BTREE_H__RAND936129428292858383414475510299913269 */
