//
// Created by patrickgeorge1 on 5/6/20.
//

#ifndef BOOKLIBRARY_BUFFER_H
#define BOOKLIBRARY_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFLEN 4096
#define LINELEN 1000

#define HEADER_TERMINATOR "\r\n\r\n"
#define HEADER_TERMINATOR_SIZE (sizeof(HEADER_TERMINATOR) - 1)
#define CONTENT_LENGTH "Content-Length: "
#define CONTENT_LENGTH_SIZE (sizeof(CONTENT_LENGTH) - 1)

typedef struct {
    char *data;
    size_t size;
} buffer;

// initializes a buffer
buffer buffer_init(void);

// destroys a buffer
void buffer_destroy(buffer *buffer);

// adds data of size data_size to a buffer
void buffer_add(buffer *buffer, const char *data, size_t data_size);

// checks if a buffer is empty
int buffer_is_empty(buffer *buffer);

// finds data of size data_size in a buffer and returns its position
int buffer_find(buffer *buffer, const char *data, size_t data_size);

// finds data of size data_size in a buffer in a
// case-insensitive fashion and returns its position
int buffer_find_insensitive(buffer *buffer, const char *data, size_t data_size);

#endif //BOOKLIBRARY_BUFFER_H
