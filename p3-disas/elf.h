/***********************************************************

    D O   N O T    M O D I F Y   T H I S   F I L E

************************************************************/

#ifndef __CS261_ELF__
#define __CS261_ELF__

#include <stdio.h>
#include <stdint.h>

#include "y86.h"

/*
   Mini-ELF file format (byte 0 = first byte of the file)
   +-------------------------------------------------------+
   | header (elf_hdr_t) - 16 bytes                         |
   +-------------------------------------------------------+
   | program headers (elf_phdr_t) - 20 bytes each          |
   +-------------------------------------------------------+
   | program segments - variable length of bytes           |
   +-------------------------------------------------------+
   | optional symbol table - each entry is 4 bytes each    |
   +-------------------------------------------------------+
   | optional string table - variable length of strings    |
   +-------------------------------------------------------+

   ELF header structure:
   +----------------------------------------------------------------------------+
   |  0   1  |  2   3  |  4   5  |  6   7  |  8   9  | 10  11  | 12  13  14  15 |
   | version | entry   | phdr    | numphdr | symtab  | strtab  | magic number   |
   +----------------------------------------------------------------------------+

    If symtab is 0 , then there is no symbol table in this mini-ELF file
    If strtab is 0 , then there is no string table in this mini-ELF file
   
   Sample ELF header (all entries in hex, format is little endian):
   +----------------------------------------------------------------------------+
   |  01  00 |  00  01 |  10  00 |  05  00 |  ac  00 |  c2  00 | 45  4c  46  00 |
   | version | entry   | phdr    | numphdr | symtab  | strtab  | magic number   |
   +----------------------------------------------------------------------------+

   version = 0x0001     entry = 0x0100      phdr = 0x0010     numphdr = 0x0005
   symtab = 0x00ac      strtab = 0x00c2     magic = "ELF\0"

   Interpretation:
   This file was created under version 1 of this format. When the program is
   loaded into memory, the instruction at address 0x0100 (256) will be executed
   first. The first program header (which indicates segments in this file)
   starts at offset 0x0010 (16) into the file, and there are 0005 program headers
   total. The symbol table starts at offset 0x00ac (172) into this file, and the
   string table starts at offset 0xc2 (194). The magic number is the character 
   string "ELF\0", alternatively read as the number 0x00464c45, and is for 
   error checking.
*/
typedef struct __attribute__((__packed__)) elf {
    uint16_t e_version;     /* version should be 1 */
    uint16_t e_entry;       /* entry point of program */
    uint16_t e_phdr_start;  /* start of program headers */
    uint16_t e_num_phdr;    /* number of program headers */
    uint16_t e_symtab;      /* start of symbol table , or zero if none */
    uint16_t e_strtab;      /* start of string table , or zero if none */
    uint32_t magic;         /* ELF */
} elf_hdr_t;

typedef enum {
    DATA, CODE, STACK, HEAP, UNKNOWN
} elf_segtype_t;

typedef enum {
    RO = 4, RX = 5, RW = 6
} elf_segflag_t;  // Think of the remaining five segFlag 3-bit values

/*
   ELF program header structure:
   +-----------------------------------------------------------------------+
   |  0  1  2  3 |  4  5  6  7 |  8  9 10 11 | 12 13 | 14 15 | 16 17 18 19 |
   | offset      | file size   | virt addr   | type  | flags | magic number|
   +-----------------------------------------------------------------------+

   Sample ELF program header (all entries in hex, format is little endian):
   +-----------------------------------------------------------------------+
   | 74 00 00 00 | 12 00 00 00 | 00 01 00 00 | 01 00 | 01 00 | ef be ad de |
   | offset      | file size   | virt addr   | type  | flags | magic number|
   +-----------------------------------------------------------------------+

   offset = 0x00000074    file size = 0x00000012      virt addr = 0x00000100
   type = 0x0001 (CODE)   flags = 0x0001 (no write)   magic = 0xDEADBEEF

   Interpretation:
   The segment starts at offset 0x74 (116) in the file, and it is 0x12 (18)
   bytes in size. It will be loaded into memory address 0x100 (256). Since it
   is a CODE segment, it will have execute permissions attached. Since its
   flag is 1, it will not be writable. The magic number is the value 0xDEADBEEF
   and is for error checking.
*/
typedef struct __attribute__((__packed__)) elf_phdr {
    uint32_t p_offset;      /* offset within the file */
    uint32_t p_filesz;      /* number of bytes in the segment */
    uint32_t p_vaddr;       /* virtual address in memory */
    uint16_t p_type;        /* code or data */
    uint16_t p_flag;        /* flag bit 2 for Read, bit 1 for Write, bit 0 for eXecute */
    uint32_t magic;         /* DEADBEEF */
} elf_phdr_t;

#endif
