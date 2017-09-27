#ifndef __PAGE_H__RAND1941219049611804134921828417981657522
#define __PAGE_H__RAND1941219049611804134921828417981657522

#include <stdint.h>
#include "io.h"


typedef struct file_pages_t file_pages_t;

typedef uint32_t page_no_t;
#define PAGE_NO_NULL 0

void file_pages_init(file_pages_t* file_pages, io_file_t* io_file);
void file_pages_format(io_file_t* io_file);
void page_read(file_pages_t* file_pages, page_no_t no, char buf[]);
void page_write(file_pages_t* file_pages, page_no_t no, const char buf[]);

page_no_t page_alloc(file_pages_t* file_pages);
void page_free(file_pages_t* file_pages, page_no_t no);

#endif /* __PAGE_H__RAND1941219049611804134921828417981657522 */
