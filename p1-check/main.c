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
    char* fname;
    bool header_need_dumped; // B_just_check_header
    elf_hdr_t header;
    if (!parse_command_line_p1(argc, argv, &header_need_dumped, &fname))
    {
        exit(EXIT_FAILURE);
    }
    if(!fname)
    {
        exit(EXIT_SUCCESS);
    }
    FILE* fp = fopen(fname, "r");
    if(!fp)
    {
        puts("Failed to read file");
		exit(EXIT_FAILURE);
    }
    if(!read_header(fp, &header))
    {
        puts("Failed to read file");
		exit(EXIT_FAILURE);
    }
	if(header_need_dumped != 0)
	{
		dump_header(header);
	}
    fclose (fp);
    return EXIT_SUCCESS;
}

