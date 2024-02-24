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
    // h: print help message
    // H: check elf header
    int opt = 0;
    while ((opt = getopt(argc, argv, "hH")) != -1) 
    {
        switch (opt)
        {
            case 'h':
                usage_p1();
                *header = false;
                *file = NULL;
                return true;
            case 'H':
                if (argc == 2)
                {
                    // handle missing filename
                    usage_p1();
                    return false;
                }
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
    if(!file || !hdr)
    {
        return false;
    }
    if(fread(hdr, sizeof(elf_hdr_t), 1, file) == -1)
    {
        return false;
    }
    if (hdr->magic != ntohl(0x454C4600))
	{
		//bad magic number
		return false;
	}
    return true;
}

void dump_header (elf_hdr_t hdr)
{
    // Implement this function
    // printf("%x ", hdr.e_version);
    // printf("%x ", hdr.e_entry);
    // printf("%x ", hdr.e_phdr_start);
    // printf("%x ", hdr.e_num_phdr);
    // printf("%x ", hdr.e_symtab);
    // printf("%x ", hdr.e_strtab);
    // printf("%x ", hdr.magic);
    // printf("Mini-ELF version 1");
    // printf("Entry point 0x100");

}

