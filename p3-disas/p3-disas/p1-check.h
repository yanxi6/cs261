/***********************************************************

    D O   N O T    M O D I F Y   T H I S   F I L E

************************************************************/

#ifndef __CS261_P1__
#define __CS261_P1__

#include <stdbool.h>

#include "elf.h"

void usage_p1 ();
bool parse_command_line_p1 ( int argc, char **argv, bool *header, char **file );

bool read_header ( FILE *file, elf_hdr_t *hdr );
void dump_header ( elf_hdr_t hdr );

#endif
