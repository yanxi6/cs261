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
    return false;
}

bool read_header (FILE *file, elf_hdr_t *hdr)
{
    // Implement this function
    return false;
}

void dump_header (elf_hdr_t hdr)
{
    // Implement this function
}

