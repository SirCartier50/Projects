#include "io.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct buffer {
    int fd;
    int offset;
    int num_remaining;
    uint8_t a[BUFFER_SIZE];
} Buffer;

Buffer *read_open(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        return NULL;
    } else {
        Buffer *buf = calloc(1, sizeof(Buffer));
        buf->fd = fd;
        return buf;
    }
}
void read_close(Buffer **pbuf) {
    close((*pbuf)->fd);
    free((*pbuf));
    *pbuf = NULL;
}

Buffer *write_open(const char *filename) {
    int fd = creat(filename, 0664);
    if (fd < 0) {
        return NULL;
    } else {
        Buffer *buf = calloc(1, sizeof(Buffer));
        buf->fd = fd;
        printf("%d\n", buf->fd);
        return buf;
    }
}
void write_close(Buffer **pbuf) {
    write((*pbuf)->fd, (*pbuf)->a, (*pbuf)->offset);
    close((*pbuf)->fd);
    free((*pbuf));
    *pbuf = NULL;
}
bool read_uint8(Buffer *buf, uint8_t *x) {
    if (buf->num_remaining == 0) {
        ssize_t rc = read(buf->fd, buf->a, sizeof(buf->a));
        if (rc < 0) {
            printf("Error\n");
            return false;
        }
        if (rc == 0) {
            return false;
        }
        buf->num_remaining = rc;
        buf->offset = 0;
    }
    *x = buf->a[buf->offset];
    buf->num_remaining--;
    buf->offset++;
    return true;
}
bool read_uint16(Buffer *buf, uint16_t *x) {
    uint8_t first_byte;
    uint8_t second_byte;
    bool first_read_check;
    bool second_read_check;
    uint16_t temp;
    first_read_check = read_uint8(buf, &first_byte);
    second_read_check = read_uint8(buf, &second_byte);
    if (!first_read_check || !second_read_check) {
        return false;
    } else {
        temp = second_byte << 8;
        *x = first_byte | temp;
        return true;
    }
}
bool read_uint32(Buffer *buf, uint32_t *x) {
    uint16_t first_halfword;
    uint16_t second_halfword;
    bool first_read_check;
    bool second_read_check;
    uint32_t temp;
    first_read_check = read_uint16(buf, &first_halfword);
    second_read_check = read_uint16(buf, &second_halfword);
    if (!first_read_check || !second_read_check) {
        return false;
    } else {
        temp = second_halfword << 16;
        *x = first_halfword | temp;
        return true;
    }
}
void write_uint8(Buffer *buf, uint8_t x) {
    if (buf->offset == BUFFER_SIZE) {
        uint8_t *start = buf->a;
        int num_bytes = buf->offset;
        do {
            ssize_t rc = write(buf->fd, start, num_bytes);
            if (rc < 0) {
                fprintf(stderr, "Error\n");
                exit(1);
            }
            start += rc;
            num_bytes -= rc;
        } while (num_bytes > 0);
        buf->offset = 0;
    }
    buf->a[buf->offset] = x;
    buf->offset++;
}
void write_uint16(Buffer *buf, uint16_t x) {
    uint8_t first_byte = x;
    uint8_t second_byte = x >> 8;
    write_uint8(buf, first_byte);
    write_uint8(buf, second_byte);
}
void write_uint32(Buffer *buf, uint32_t x) {
    uint16_t first_halfword = x;
    uint16_t second_halfword = x >> 16;
    write_uint16(buf, first_halfword);
    write_uint16(buf, second_halfword);
}
