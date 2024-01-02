#include "bmp.h"
#include "io.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define OPTIONS "i:o:dh"
void help_message(void) {
    printf("SYNOPSIS\n Command options that specifies if the user wants to use an inputfile, to "
           "write the output to a file, and if the graph is a directed graph..\nUSAGE\n   "
           "./tsp6 [-i inputfile name] [-o outputfile name] [-dh]\n\nOPTIONS\n   -H         "
           "     Display program help and usage.\n   -i              Reads the given input file.\n "
           "  -o      "
           "        Writes to the given output file.\n   -d              Changes graph to a "
           "directed graph\n");
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
            fprintf(stderr,
                "SYNOPSIS\n Command options that specifies if the user wants to use an inputfile, "
                "to "
                "write the output to a file, and if the graph is a directed graph..\nUSAGE\n   "
                "./tsp6 [-i inputfile name] [-o outputfile name] [-dh]\n\nOPTIONS\n   -H         "
                "     Display program help and usage.\n   -i              Reads the given input "
                "file.\n "
                "  -o      "
                "        Writes to the given output file.\n   -d              Changes graph to a "
                "directed graph\n");
            return 0;
        }
    }
    if (flag_h) {
        help_message();
        return 0;
    }
    if (input_filename == NULL || output_filename == NULL) {
        fprintf(stderr,
            "SYNOPSIS\n Command options that specifies if the user wants to use an inputfile, "
            "to "
            "write the output to a file, and if the graph is a directed graph..\nUSAGE\n   "
            "./tsp6 [-i inputfile name] [-o outputfile name] [-dh]\n\nOPTIONS\n   -H         "
            "     Display program help and usage.\n   -i              Reads the given input "
            "file.\n "
            "  -o      "
            "        Writes to the given output file.\n   -d              Changes graph to a "
            "directed graph\n");
        return 0;
    }

    Buffer *read_buf = read_open(input_filename);
    if (read_buf == NULL) {
        fprintf(stderr, "error creating read buffer!\n");
        return 0;
    }
    Buffer *write_buf = write_open(output_filename);
    if (write_buf == NULL) {
        read_close(&read_buf);
        fprintf(stderr, "error  creating a write buffer!\n");
        return 0;
    }
    BMP *bmp = bmp_create(read_buf);
    if (bmp == NULL) {
        read_close(&read_buf);
        write_close(&write_buf);
        fprintf(stderr, "error  creating!\n");
        return 0;
    }
    bmp_reduce_palette(bmp);
    bmp_write(bmp, write_buf);
    read_close(&read_buf);
    write_close(&write_buf);
    bmp_free(&bmp);
    return 0;
}
