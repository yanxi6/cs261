/*
 * CS 261: Main driver
 *
 * Name:    MUST  WRITE    YOUR    NAME    HERE
 */

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "elf.h"
#include "p1-check.h"

int main (int argc, char **argv)
{
    // Write code to call the parse function then 
    // open the elf file, read its header, and react depending on whether -H was present
    char *fname = "tests/inputs/simple.o";
    FILE* fp = fopen(fname, "r");
    // elf_hdr_t *hdr;
    char data[8];
    fread(data, 8, 1, fp);
    for(int i = 0; i < 8; i++)
    {
        printf("%x ", data[i]);
    }
    printf("\n");
    // read_header(fname);
    fclose(fp);
    return EXIT_SUCCESS;
}

