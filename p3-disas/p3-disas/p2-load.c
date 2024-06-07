/*
 * CS 261 PA2: Mini-ELF loader
 *
 * Name: WRITE  YOUR FULL NAME HERE
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "p2-load.h"

void usage_p2 ()
{

}

bool parse_command_line_p2 (int argc, char **argv,
        bool *header, bool *segments, bool *membrief, bool *memfull,
        char **file)
{
    return true;
}

bool read_phdr (FILE *file, uint16_t offset, elf_phdr_t *phdr)
{
    return true;
}

void dump_phdrs (uint16_t numphdrs, elf_phdr_t phdr[])
{
}

bool load_segment (FILE *file, memory_t memory, elf_phdr_t phdr)
{
    return true;
}

void dump_memory (memory_t memory, uint16_t start, uint16_t end)
{
}
