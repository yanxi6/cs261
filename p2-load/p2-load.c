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
    // Missing code here
    printf("Usage: y86 <option(s)> mini-elf-file\n");
    printf(" Options are:\n");
    printf("  -h      Display usage\n");
    printf("  -H      Show the Mini-ELF header\n");
    printf("  -a      Show all with brief memory\n");
    printf("  -f      Show all with full memory\n");
    printf("  -s      Show the program headers\n");
    printf("  -m      Show the memory contents (brief)\n");
    printf("  -M      Show the memory contents (full)\n");
    printf("Options must not be repeated neither explicitly nor implicitly.\n");
}

bool parse_command_line_p2 (int argc, char **argv,
        bool *header, bool *segments, bool *membrief, bool *memfull,
        char **file)
{
    int opt = 0;
    while ((opt = getopt(argc, argv, "+hHafsmM")) != -1) 
    {
        switch (opt)
        {
            case 'h':
                usage_p2();
                *header = false;
                *file = NULL;
                return true;
            case 'H':
                *header = true;
                *file = NULL;
                break;
            case 'a':
                break;
            case 'f':
                break;
            case 's':
                break;
            case 'm':
                *membrief = true;
                break;
            case 'M':
                *memfull = true;
                break;
            default:
                // invalid options
                usage_p2();
                *header = false;
                *file = NULL;
                return false;
        }
    }
    *file = argv[optind];
    return true;
}

bool read_phdr (FILE *file, uint16_t offset, elf_phdr_t *phdr)
{
    // Read a Mini-ELF program header from file into the space pointed to by phdr, 
    // starting from byte offset in the file. 
    // If the reading fails or it is not a valid program header 
    // (e.g., the magic number is incorrect), return false.
    elf_hdr_t hdr;
    if(!file || !phdr)
    {
        return false;
    }
    // if(fread(hdr, sizeof(elf_hdr_t), 1, file) == -1)
    // {
    //     return false;
    // }
    fseek(file, offset, SEEK_SET);
    if(fread(phdr, sizeof(elf_phdr_t), 1, file) == -1)
    {
        return false;
    }
    // if (hdr.magic != ntohl(0x454C4600))
	// {
	// 	//bad magic number
	// 	return false;
	// }
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
