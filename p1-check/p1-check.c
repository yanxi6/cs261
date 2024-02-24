/*
 * CS 261 PA1: Mini-ELF header verifier
 *
 * Name:     MUST   WRITE    YOUR    NAME    HERE
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "p1-check.h"

void usage_p1 ()
{
    printf("Usage: y86 <option(s)> mini-elf-file\n");
    printf(" Options are:\n");
    printf("  -h      Display usage\n");
    printf("  -H      Show the Mini-ELF header\n");
    printf("Options must not be repeated neither explicitly nor implicitly.\n");
}

bool parse_command_line_p1 (int argc, char **argv, bool *header, char **file)
{
    // Implement this function
    // Read system argv and parsing
    int opt;
    while ((opt = getopt(argc, argv, "+hH")) != -1) 
    {
        switch (opt)
        {
            case 'h':
                usage_p1();
                *header = false;
                *file = NULL;
                return true;
            case 'H':
                *header = true;
                *file = NULL;
                break;
            default:
            // invalid options
                usage_p1();
                *header = false;
                *file = NULL;
                return false;
        }
    }
    *file = argv[optind];
    return true;
}

bool read_header (FILE *file, elf_hdr_t *hdr)
{
    // Implement this function
    // fread(data, 8, 1, fp);
    return false;
}

void dump_header (elf_hdr_t hdr)
{
    // Implement this function
}

