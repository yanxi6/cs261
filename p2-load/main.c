/*
 *  CS 261 PA2: Mini-ELF loader Main driver
 *
 * Name:  WRITE  YOUR FULL NAME HERE
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "p1-check.h"
#include "p2-load.h"

int main (int argc, char **argv)
{
    // char* fname;
    // bool header_need_dumped; // B_just_check_header
    // bool segments; 
    // bool membrief; 
    // bool memfull;
    // elf_hdr_t header;
    // if (!parse_command_line_p2(argc, argv, &header_need_dumped, &segments, 
    //     &membrief, &memfull, &fname))
    // {
    //     exit(EXIT_FAILURE);
    // }

    FILE *fp = fopen ("tests/inputs/stripped.o", "r");
    uint16_t offset = 0x10;
    elf_phdr_t phdr;
    bool rc = false;


    rc = read_phdr (fp, offset, &phdr);
    return EXIT_SUCCESS;
}

