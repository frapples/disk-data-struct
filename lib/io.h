#ifndef __IO_H__RAND5104581976470232452288340069304669069
#define __IO_H__RAND5104581976470232452288340069304669069

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef uint64_t io_off_t;

typedef struct {
    char* mem;
    io_off_t len;
    io_off_t size;
}MemFile;

typedef struct {
    union {
        FILE* file;
        MemFile* mem_file;
    };
    bool is_mem;
}IoFile;


IoFile* io_open(const char* file_path, const char* mode);
size_t io_read(IoFile* file, io_off_t off, char* buf, size_t size);
size_t io_write(IoFile* file, io_off_t off, char* buf, size_t size);
void io_close(IoFile* file);

#endif /* __IO_H__RAND5104581976470232452288340069304669069 */
