/*had help from tutors lev and tony. Also from ben and jess*/
#include "bitwriter.h"
#include "io.h"
#include "pq.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define OPTIONS "i:o:dh"

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

void help_message(void) {
    fprintf(stdout,
        "SYNOPSIS\n Command options that specifies if the user wants to use an inputfile and "
        "to "
        "write the output to a file.\nUSAGE\n   "
        "./huff [-i inputfile name] [-o outputfile name] [-h]\n\nOPTIONS\n   -h         "
        "     Display program help and usage.\n   -i              Reads the given input "
        "file.\n "
        "  -o      "
        "        Writes to the given output file.\n");
}
uint64_t fill_histogram(Buffer *inbuf, double *histogram) {
    uint8_t element;
    bool check;
    uint64_t filesize = 0;
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }
    while (true) {
        check = read_uint8(inbuf, &element);
        if (check == false) {
            break;
        }
        ++histogram[element];
        ++filesize;
    }
    ++histogram[0x00];
    ++histogram[0xff];
    return filesize;
}
Node *create_tree(double *histogram, uint16_t *num_leaves) {
    PriorityQueue *pq = pq_create();
    for (int i = 0; i < 256; i++) {
        if (histogram[i] != 0) {
            Node *new_node = node_create(i, histogram[i]);
            enqueue(pq, new_node);
            (*num_leaves)++;
        }
    }
    Node *left;
    Node *right;
    while (!pq_size_is_1(pq)) {
        dequeue(pq, &left);
        dequeue(pq, &right);
        Node *node = node_create('$', left->weight + right->weight);
        node->left = left;
        node->right = right;
        enqueue(pq, node);
    }
    dequeue(pq, &left);
    pq_free(&pq);
    return left;
}
void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left != NULL || node->right != NULL) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left != NULL || node->right != NULL) {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    } else {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    }
}
void huff_compress_file(BitWriter *outbuf, Buffer *inbuf, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    uint8_t byte;
    uint64_t code;
    uint8_t code_length;
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);
    while (read_uint8(inbuf, &byte)) {
        code = code_table[byte].code;
        code_length = code_table[byte].code_length;
        for (uint8_t i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
}
void post_order(Node *cur) {
    if (cur == NULL) {
        return;
    } else {
        post_order(cur->left);
        post_order(cur->right);
        node_free(&cur);
    }
}
int main(int argc, char **argv) {
    bool flag_h = false;
    char *input_filename = NULL;
    char *output_filename = NULL;
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': input_filename = optarg; break;
        case 'o': output_filename = optarg; break;
        case 'h': flag_h = true; break;
        default:
            fprintf(stderr, "SYNOPSIS\n Command options that specifies if the user wants to "
                            "use an inputfile "
                            "and "
                            "to "
                            "write the output to a file.\nUSAGE\n   "
                            "./huff [-i inputfile name] [-o outputfile name] "
                            "[-h]\n\nOPTIONS\n   -h         "
                            "     Display program help and usage.\n   -i              Reads "
                            "the given input "
                            "file.\n "
                            "  -o      "
                            "        Writes to the given output file.\n");
            return 0;
        }
    }
    if (flag_h) {
        help_message();
        return 0;
    }
    if (input_filename == NULL || output_filename == NULL) {
        fprintf(stderr,
            "SYNOPSIS\n Command options that specifies if the user wants to use an inputfile and "
            "to "
            "write the output to a file.\nUSAGE\n   "
            "./colorb [-i inputfile name] [-o outputfile name] [-h]\n\nOPTIONS\n   -h         "
            "     Display program help and usage.\n   -i              Reads the given input "
            "file.\n "
            "  -o      "
            "        Writes to the given output file.\n");
        return 0;
    }

    Buffer *histobuf = read_open(input_filename);
    double *histogram = calloc(256, sizeof(double));
    uint64_t filesize = fill_histogram(histobuf, histogram);
    read_close(&histobuf);
    uint16_t num_leaves = 0;
    Node *code_tree = create_tree(histogram, &num_leaves);
    Code *code_table = calloc(256, sizeof(Code));
    fill_code_table(code_table, code_tree, 0, 0);
    Buffer *inbuf = read_open(input_filename);
    BitWriter *outbuf = bit_write_open(output_filename);
    huff_compress_file(outbuf, inbuf, filesize, num_leaves, code_tree, code_table);
    bit_write_close(&outbuf);
    read_close(&inbuf);
    free(histogram);
    histogram = NULL;
    free(code_table);
    code_table = NULL;
    post_order(code_tree);

    return 0;
}
