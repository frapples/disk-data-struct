#include "io.h"

#include <string.h>
#include <stdlib.h>

static void memfile_init(mem_file_t* mem_file);
static void memfile_close(mem_file_t* mem_file);
static io_off_t memfile_read(mem_file_t* mem_file, io_off_t off, char* buf, size_t size);
static io_off_t memfile_write(mem_file_t* mem_file, io_off_t off, char* buf, size_t size);

io_file_t* io_open(const char* file_path, const char* mode)
{
    io_file_t* file;
    if (strcmp(file_path, ":memory:") == 0) {
        void* m = malloc(sizeof(*file) + sizeof(mem_file_t));
        file = m;
        file->mem_file = m + sizeof(*file);
        file->is_mem = true;
        memfile_init(file->mem_file);
    } else {
        file = malloc(sizeof(*file));
        file->is_mem = false;
        file->file = fopen(file_path, mode);
    }
    return file;
}

io_off_t io_read(io_file_t* file, io_off_t off, char* buf, size_t size)
{
    if (file->is_mem) {
        return memfile_read(file->mem_file, off, buf, size);
    } else {
        fseek(file->file, off, SEEK_SET);
        return fread(buf, sizeof(*buf), size, file->file);
    }
}

io_off_t io_write(io_file_t* file, io_off_t off, char* buf, size_t size)
{
    if (file->is_mem) {
        return memfile_write(file->mem_file, off, buf, size);
    } else {
        fseek(file->file, off, SEEK_SET);
        return fwrite(buf, sizeof(*buf), size, file->file);
    }
}

void io_close(io_file_t* file)
{
    if (file->is_mem) {
        memfile_close(file->mem_file);
    } else {
        fclose(file->file);
    }
    free(file);
}

static void memfile_init(mem_file_t* mem_file)
{
    mem_file->size = 512;
    mem_file->mem = malloc(mem_file->size * sizeof(char));
    mem_file->len = 0;
}

static void memfile_close(mem_file_t* mem_file)
{
    free(mem_file->mem);
}

static io_off_t memfile_read(mem_file_t* mem_file, io_off_t off, char* buf, size_t size)
{
    io_off_t cpy_size = mem_file->len < off + size ? mem_file->len - off : size;
    memcpy(buf, mem_file->mem + off, cpy_size);
    return cpy_size;
}

static io_off_t memfile_write(mem_file_t* mem_file, io_off_t off, char* buf, size_t size)
{
    if (off + size > mem_file->size) {
        mem_file->size *= 2;
        mem_file->mem = realloc(mem_file->mem, mem_file->size);
        return memfile_write(mem_file, off, buf, size);
    } else {
        memcpy(mem_file->mem + off, buf, size);
        mem_file->len = mem_file->len > off + size ? mem_file->len : off + size;
        return size;
    }
}
