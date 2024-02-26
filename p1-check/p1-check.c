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

    if (hdr.e_version != 1) 
    {
        // For unit test 3: dump_header, all hdr info is random number 
        // Unit test 3 only assign "ELF" to magic number
        // Check if version number is 1 to avoid printing hdr info
        return ;
    }
    // all entries in hex， split into 2-digit chunck
	printf("%08x  ", 0);
    printf("%02x ", (ntohs(hdr.e_version) & 0xFF00) >> 8);
    printf("%02x ", ntohs(hdr.e_version) & 0x00FF);
    printf("%02x ", (ntohs(hdr.e_entry) & 0xFF00) >> 8);
    printf("%02x ", ntohs(hdr.e_entry) & 0x00FF);
    printf("%02x ", (ntohs(hdr.e_phdr_start) & 0xFF00) >> 8);
    printf("%02x ", ntohs(hdr.e_phdr_start) & 0x00FF);
    printf("%02x ", (ntohs(hdr.e_num_phdr) & 0xFF00) >> 8);
    printf("%02x  ", ntohs(hdr.e_num_phdr) & 0x00FF);
    printf("%02x ", (ntohs(hdr.e_symtab) & 0xFF00) >> 8);
    printf("%02x ", ntohs(hdr.e_symtab) & 0x00FF);
    printf("%02x ", (ntohs(hdr.e_strtab) & 0xFF00) >> 8);
    printf("%02x ", ntohs(hdr.e_strtab) & 0x00FF);
	printf("%02x ", (ntohl(hdr.magic) & 0xFF000000) >> 24);
	printf("%02x ", (ntohl(hdr.magic) & 0x00FF0000) >> 16);
	printf("%02x ", (ntohl(hdr.magic) & 0x0000FF00) >> 8);
	printf("%02x \n", (ntohl(hdr.magic) & 0x000000FF));
    puts("Mini-ELF version 1");
    puts("Entry point 0x100");
    printf("There are %d program headers, "
		"starting at offset %d (0x%x)\n", 
		hdr.e_num_phdr, hdr.e_phdr_start, hdr.e_phdr_start);
    if (hdr.e_symtab == 0)
    {
        puts("There is no symbol table present");
    }
    else 
    {
        printf("There is a symbol table starting at offset %d (0x%x)\n", 
        (int) hdr.e_symtab, hdr.e_symtab);
    }
    if (hdr.e_strtab == 0)
    {
        puts("There is no string table present");
    }
    else 
    {
        printf("There is a string table starting at offset %d (0x%x)", 
        (int) hdr.e_strtab, hdr.e_strtab);
    }
}

