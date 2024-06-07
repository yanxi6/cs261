/***********************************************************

    D O   N O T    M O D I F Y   T H I S   F I L E

************************************************************/

#ifndef __CS261_Y86__
#define __CS261_Y86__

#include <stdint.h>
#include <stdbool.h>

#define VADDRBITS 12
#define MEMSIZE (1 << VADDRBITS)
#define NUMREGS 15

/* type declarations */
typedef uint8_t  *memory_t;        /* memory array */
typedef uint64_t  y86_register_t;  /* registers */
typedef uint8_t   y86_rnum_t;      /* register number */
typedef uint64_t  address_t;       /* addresses */
typedef bool      flag_t;          /* CPU flag */

/* possible CPU statuses */
typedef enum { AOK = 1, HLT, ADR, INS } y86_stat_t;

/* Y86 CPU data storage structure
   There are 15 general-purpose registers, 3 flags, the PC, and the status */
typedef struct y86 {

    /* 64-bit general-purpose registers */
    y86_register_t rax;   /* register 0 */
    y86_register_t rcx;   /* register 1 */
    y86_register_t rdx;   /* register 2 */
    y86_register_t rbx;   /* register 3 */
    y86_register_t rsp;   /* register 4 - stack pointer */
    y86_register_t rbp;   /* register 5 - base pointer */
    y86_register_t rsi;   /* register 6 */
    y86_register_t rdi;   /* register 7 */
    y86_register_t r8;    /* register 8 */
    y86_register_t r9;    /* register 9 */
    y86_register_t r10;   /* register 10 */
    y86_register_t r11;   /* register 11 */
    y86_register_t r12;   /* register 12 */
    y86_register_t r13;   /* register 13 */
    y86_register_t r14;   /* register 14 */

    flag_t zf;            /* zero flag */
    flag_t sf;            /* negative flag */
    flag_t of;            /* overflow flag */

    y86_register_t pc;    /* program counter */

    y86_stat_t stat;      /* program status */
} y86_t;

/* Y86 instruction encoding:
            byte:   |   0   |   1   | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
   halt             |  0  0 |
   nop              |  1  0 |
   cmovXX rA, rB    |  2 fn | rA rB |
   irmovq V, rB     |  3  0 |  f rB |               V               |
   rmmovq rA, D(rB) |  4  0 | rA rB |               D               |
   mrmovq D(rB), rA |  5  0 | rA rB |               D               |
   OPq rA, rB       |  6 fn | rA rB |
   jXX Dest         |  7 fn |                Dest               |
   call Dest        |  8  0 |                Dest               |
   ret              |  9  0 |
   pushq rA         |  A  0 | rA  f |
   popq rA          |  B  0 | rA  f |

   cmovXX:
            rrmovq  20
            cmovle  21
            cmovl   22
            cmove   23
            cmovne  24
            cmovge  25
            cmovg   26

   OPl:
            addq    60
            subq    61
            andq    62
            xorq    63

   jXX:
            jmp     70
            jle     71
            jl      72
            je      73
            jne     74
            jge     75
            jg      76
 */

typedef enum {
    RAX = 0, RCX, RDX, RBX, RSP, RBP, RSI, RDI,
    R8, R9, R10, R11, R12, R13, R14, BADREG
} y86_regname_t;

/* These enums are specified to match the order of the numbers for all Y86
   instructions and operands. As such, they MUST be used as constants throughout
   the code. 
*/

typedef enum {
    HALT = 0, NOP, CMOV, IRMOVQ, RMMOVQ, MRMOVQ, OPQ, JUMP, CALL, RET, PUSHQ,
    POPQ, INVALID
} y86_inst_class_t;

typedef enum {
    RRMOVQ = 0, CMOVLE, CMOVL, CMOVE, CMOVNE, CMOVGE, CMOVG, BADCMOV
} y86_cmov_t;

typedef enum {
    ADD = 0, SUB, AND, XOR, BADOP
} y86_op_t;

typedef enum {
    JMP = 0, JLE, JL, JE, JNE, JGE, JG, BADJUMP
} y86_jump_t;

/* Layout of the structure representing a Y86 Instruction 
   use the constants defined in the enums above to fill the fields
*/
typedef struct y86_inst {
        y86_inst_class_t  type;   // which inst_class is this instruction?
        y86_cmov_t        cmov;   // For CMOV, which y86_comov_t is it?
        y86_op_t          op;     // For OPQ,  which y86_op_t is it?
        y86_jump_t        jump;   // For JUMP, which y86_jump_t is it?
        y86_rnum_t        ra;
        y86_rnum_t        rb;
        address_t         dest;   // For JUMP and CALL, what is the destination ?
        int64_t           value;  // For IRMOVQ, what is the immediate value 'V' ?
        int64_t           d;      // For RMMOVQ and MRMOVQ, what is the Displacement 'D' ?
        uint8_t           size;   // Size of this instruction in Bytes
        uint8_t           opcode; // The entire first byte of this instruction
} y86_inst_t;

#endif