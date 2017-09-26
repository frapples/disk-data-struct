#ifndef __IO_H__RAND5104581976470232452288340069304669069
#define __IO_H__RAND5104581976470232452288340069304669069

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef uint64_t io_off_t;
typedef struct io_file_t io_file_t;


io_file_t* io_open(const char* file_path, const char* mode);
size_t io_read(io_file_t* file, io_off_t off, char* buf, size_t size);
size_t io_write(io_file_t* file, io_off_t off, const char* buf, size_t size);
void io_close(io_file_t* file);

#endif /* __IO_H__RAND5104581976470232452288340069304669069 */
