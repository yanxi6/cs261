/*
 * CS 261 PA3: Mini-ELF disassembler
 *
 * Name: 
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "p3-disas.h"

//============================================================================
void usage_p3 ()
{

}

//============================================================================
bool parse_command_line_p3 (int argc, char **argv,
        bool *header, bool *segments, bool *membrief, bool *memfull,
        bool *disas_code, bool *disas_data, char **file)
{
    return true;
}

//============================================================================
y86_inst_t fetch (y86_t *cpu, memory_t memory)
{
    y86_inst_t ins;

    // Initialize the instruction
    memset( &ins , 0 , sizeof(y86_inst_t) );  // Clear all fields i=on instr.    
    ins.type = INVALID;   // Invalid instruction until proven otherwise

    return ins;
}

//============================================================================
void disassemble (y86_inst_t inst)
{
}

//============================================================================
void disassemble_code (memory_t memory, elf_phdr_t *phdr, elf_hdr_t *hdr)
{
}

//============================================================================
void disassemble_data (memory_t memory, elf_phdr_t *phdr)
{
}

//============================================================================
void disassemble_rodata (memory_t memory, elf_phdr_t *phdr)
{
}
//============================================================================

