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
    char *argv_v[] = { "./y86", "-H", "empty.o", NULL };
    bool rc = 0;
    bool header = false;
    char *file = NULL;

    rc = parse_command_line_p1 (3, argv_v, &header, &file);
    return EXIT_SUCCESS;
}

